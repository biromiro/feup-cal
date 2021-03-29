/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <set>
#include <algorithm>
#include <stdexcept>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<std::vector<size_t>> nextFloydWarshall;
    std::vector<std::vector<size_t>> matrixFloydWarshall;
public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    auto startPoint = findVertex(orig);
    if(startPoint == NULL) return;
    for(auto vertex: vertexSet){
        if(vertex == startPoint) vertex->dist = 0;
        else vertex->dist = INT_MAX;
    }
    std::queue<Vertex<T>*> points;
    std::set<Vertex<T>*> seen;
    points.push(startPoint);
    while(!points.empty()){
        auto currentPoint = points.front();
        points.pop();
        for(auto edge: currentPoint->adj){
            auto destination = edge.dest;
            if(seen.find(destination) != seen.end()) continue;
            if(destination->dist > currentPoint->dist + 1){
                destination->dist = currentPoint->dist + 1;
                destination->path = currentPoint;
                points.push(destination);
            }
        }
        seen.insert(currentPoint);
    }

}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    Vertex<T>* currentVertex = findVertex(origin);
    if(currentVertex == NULL) return;
    for(auto vertex: vertexSet){
        vertex->dist = INT_MAX;
        vertex->path = NULL;
    }
    currentVertex->dist = 0;
    MutablePriorityQueue<Vertex<T>> prioq = MutablePriorityQueue<Vertex<T>>();
    prioq.insert(currentVertex);
    while(!prioq.empty()){
        currentVertex = prioq.extractMin();
        for(auto edge: currentVertex->adj){
            auto adjacentVertex = edge.dest;
            if(adjacentVertex->dist > currentVertex->dist + edge.weight){
                auto oldDist = adjacentVertex->dist;
                adjacentVertex->dist = currentVertex->dist + edge.weight;
                adjacentVertex->path = currentVertex;
                if(oldDist == INT_MAX) prioq.insert(adjacentVertex);
                else prioq.decreaseKey(adjacentVertex);
            }
        }
    }
    return;

}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    Vertex<T>* currentVertex = findVertex(orig);
    if(currentVertex == NULL) return;
    for(auto vertex: vertexSet){
        vertex->dist = INT_MAX;
        vertex->path = NULL;
    }
    currentVertex->dist = 0;
    for(size_t i = 0; i < vertexSet.size() - 1; i++){
        for(auto vertex: vertexSet){
            for(auto edge: vertex->adj){
                auto destVertex = edge.dest;
                if(destVertex->dist > vertex->dist + edge.weight){
                    destVertex->dist = vertex->dist + edge.weight;
                    destVertex->path = vertex;
                }
            }
        }
    }
    for(auto vertex: vertexSet){
        for(auto edge: vertex->adj){
            auto destVertex = edge.dest;
            if(destVertex->dist > vertex->dist + edge.weight){
                throw std::runtime_error("There are negative cycles!");
            }
        }
    }
    return;
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    auto current = findVertex(dest);
    while(current->info != origin){
        res.push_back(current->info);
        current = current->path;
    }
    res.push_back(current->info);
    std::reverse(res.begin(),res.end());
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    matrixFloydWarshall = std::vector<std::vector<size_t>>(vertexSet.size(), std::vector<size_t>(vertexSet.size(), 0));
    nextFloydWarshall = std::vector<std::vector<size_t>>(vertexSet.size(), std::vector<size_t>(vertexSet.size(), 0));
    for(size_t i = 0; i < vertexSet.size(); i++){
        for (size_t j = 0; j < vertexSet.size(); j++){
            if(i == j) matrixFloydWarshall[i][j] = 0;
            int weight = INT_MAX;
            auto currentVertex = vertexSet[i];
            for(auto edge: currentVertex->adj){
                if(edge.dest == vertexSet[j]){
                    weight = edge.weight;
                    break;
                }
            }
            matrixFloydWarshall[i][j] = weight;
            if(weight != INT_MAX) nextFloydWarshall[i][j] = j;
        }
    }
    for(size_t k = 0; k < vertexSet.size(); k++) {
        for (size_t i = 0; i < vertexSet.size(); i++) {
            for (size_t j = 0; j < vertexSet.size(); j++) {
                if(matrixFloydWarshall[i][k] + matrixFloydWarshall[k][j] < matrixFloydWarshall[i][j]){
                    matrixFloydWarshall[i][j] = matrixFloydWarshall[i][k] + matrixFloydWarshall[k][j];
                    nextFloydWarshall[i][j] = nextFloydWarshall[i][k];
                }
            }
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;

    auto currentVertex = findVertex(orig);
    auto destinationVertex = findVertex(dest);
    auto currentVertexIt = std::find(vertexSet.begin(), vertexSet.end(), currentVertex);
    auto destinationVertexIt = std::find(vertexSet.begin(), vertexSet.end(), destinationVertex);

    if(currentVertexIt == vertexSet.end() || destinationVertexIt == vertexSet.end()) return res;

    size_t currentIndex = std::distance(vertexSet.begin(), currentVertexIt);
    size_t destinationIndex = std::distance(vertexSet.begin(),destinationVertexIt);

    if(matrixFloydWarshall[currentIndex][destinationIndex] == INT_MAX) return res;

    for(; currentIndex != destinationIndex; currentIndex = nextFloydWarshall[currentIndex][destinationIndex]){
        res.push_back(vertexSet.at(currentIndex)->info);
    }

    res.push_back(vertexSet.at(destinationIndex)->info);
    return res;
}



#endif /* GRAPH_H_ */
