/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <set>

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	std::vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	bool processing;       // auxiliary field used by isDAG
	int indegree;          // auxiliary field used by topsort

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

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
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v, std::set<Vertex<T>*> parents) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
    std::vector<T> dfs() const;
    std::vector<T> bfs(const T &source) const;
    std::vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if(findVertex(in) != NULL) return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T> * sourceVertex = findVertex(sourc);
    Vertex<T> * destVertex = findVertex(dest);
    if(sourceVertex == NULL || destVertex == NULL) return false;
    sourceVertex->addEdge(destVertex,w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d,w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * sourceVertex = findVertex(sourc);
    Vertex<T> * destVertex = findVertex(dest);
    if(sourceVertex == NULL || destVertex == NULL) return false;
    return sourceVertex->removeEdgeTo(destVertex);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    bool returnVal = false;
    auto it = std::find_if(adj.begin(), adj.end(), [&](const Edge<T>& edge){ return edge.dest == d;});
    while(it != adj.end()){
        adj.erase(it);
        it = std::find_if(adj.begin(), adj.end(), [&](const Edge<T>& edge){ return edge.dest == d;});
        returnVal = true;
    }
    return returnVal;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    auto it = std::find_if(vertexSet.begin(), vertexSet.end(),
                           [&in](const Vertex<T>* vertex){ return vertex->info == in;});
    if(it == vertexSet.end()) return false;
    for(const auto& vertex: vertexSet){
        if(vertex->info == (*it)->info) continue;
        vertex->removeEdgeTo(*it);
    }
    vertexSet.erase(it);
    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::dfs() const {
    if(vertexSet.empty()) return std::vector<T>();
    std::stack<Vertex<T>*> points;
    std::set<Vertex<T>*> visited;
    std::vector<T> res;
    points.push(vertexSet.at(0));
    while(!points.empty()){
        Vertex<T>* currentVertex = points.top();
        points.pop();
        if(visited.find(currentVertex) != visited.end()) continue;
        for(auto it = (currentVertex->adj).rbegin(); it != (currentVertex->adj).rend(); it++){
            if(visited.find(it->dest) != visited.end()) continue;
            points.push(it->dest);
        }
        visited.insert(currentVertex);
        res.push_back(currentVertex->info);
    }
    return res;
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::bfs(const T & source) const {
    Vertex<T>* start = findVertex(source);
    if(vertexSet.empty() || start == NULL) return std::vector<T>();
    std::queue<Vertex<T>*> points;
    std::set<Vertex<T>*> visited;
    std::vector<T> res;
    points.push(start);
    while(!points.empty()){
        Vertex<T>* currentVertex = points.front();
        points.pop();
        if(visited.find(currentVertex) != visited.end()) continue;
        for(const auto& edge: currentVertex->adj){
            if(visited.find(edge.dest) != visited.end()) continue;
            points.push(edge.dest);
        }
        visited.insert(currentVertex);
        res.push_back(currentVertex->info);
    }
    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {
    for(auto vertex: vertexSet) vertex->indegree = 0;
    for(auto vertex: vertexSet)
        for(auto adjedge: vertex->adj) { (adjedge.dest)->indegree += 1; }
    std::queue<Vertex<T>*> points;
    for(auto vertex: vertexSet) if(vertex->indegree == 0) points.push(vertex);
    std::vector<T> res;
    while(!points.empty()){
        auto currentVertex = points.front();
        points.pop();
        res.push_back(currentVertex->info);
        for(auto adjedge: currentVertex->adj){
            (adjedge.dest)->indegree -= 1;
            if((adjedge.dest)->indegree == 0) points.push(adjedge.dest);
        }
    }
    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
    Vertex<T>* start = findVertex(source);
    if(vertexSet.empty() || start == NULL) return 0;
    std::queue<Vertex<T>*> points;
    std::set<Vertex<T>*> visited;
    int res = 0;
    points.push(start);
    while(!points.empty()){
        Vertex<T>* currentVertex = points.front();
        points.pop();
        if(visited.find(currentVertex) != visited.end()) continue;
        int current = 0;
        for(const auto& edge: currentVertex->adj){
            if(visited.find(edge.dest) != visited.end()) continue;
            current++;
            points.push(edge.dest);
        }
        if(current > res){
            res = current;
            inf = currentVertex->info;
        }
        visited.insert(currentVertex);
    }
    return res;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    if(vertexSet.empty()) return false;
    return dfsIsDAG(vertexSet.at(0), std::set<Vertex<T>*>());
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v, std::set<Vertex<T>*> parents) const {
    if(parents.find(v) != parents.end()) return false;
    else parents.insert(v);
    for(auto edge: v->adj){
        if(!dfsIsDAG(edge.dest, parents)) return false;
    }
    return true;
}

#endif /* GRAPH_H_ */
