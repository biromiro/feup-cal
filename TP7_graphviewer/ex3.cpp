#include <fstream>
#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex3() {
    GraphViewer gv;

    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300,300));

    ifstream iNodesStream("../TP7_graphviewer/resources/map1/nodes.txt");
    GraphViewer::id_t N, idNode; int x, y;
    iNodesStream >> N;
    for(GraphViewer::id_t i = 0; i < N; ++i){
        iNodesStream >> idNode >> x >> y;
        Node &node = gv.addNode(idNode, sf::Vector2f(x, y));
    }

    ifstream iEdgesStream("../TP7_graphviewer/resources/map1/edges.txt");
    GraphViewer::id_t E, idEdge, u, v;
    iEdgesStream >> E;
    for(GraphViewer::id_t i = 0; i < E; ++i){
        iEdgesStream >> idEdge >> u >> v;
        Edge &edge = gv.addEdge(idEdge, gv.getNode(u), gv.getNode(v));
        edge.setColor(GraphViewer::BLACK);
    }
    gv.createWindow(600, 600);
    gv.join();

}

