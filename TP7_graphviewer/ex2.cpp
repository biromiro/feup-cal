#include <synchapi.h>
#include <iostream>
#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex2() {
    // Instantiate GraphViewer
    GraphViewer gv;

    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300,300));

    std::vector<std::pair<int, int>> coords = {{300,50},
                                 {318,58},
                                 {325,75},
                                 {318,93},
                                 {300,100},
                                 {282,93},
                                 {275,75},
                                 {282,58},
                                 {150,200},
                                 {300,200},
                                 {450,200},
                                 {300,400},
                                 {200,550},
                                 {400,550},
    };

    GraphViewer::id_t id = 0;
    for(auto pair: coords)
        gv.addNode(id++, sf::Vector2f(pair.first, pair.second));

    std::vector<std::pair<int, int>> edges = {{0,1},
                                 {1,2},
                                 {2,3},
                                 {3,4},
                                 {4,5},
                                 {5,6},
                                 {6,7},
                                 {7,0},
                                 {4,9},
                                 {9,8},
                                 {9,10},
                                 {9,11},
                                 {11,12},
                                 {11,13},
    };

    //id = 0;
    for(auto pair: edges)
        gv.addEdge(id++,
                   gv.getNode(pair.first),
                   gv.getNode(pair.second),
                   GraphViewer::Edge::UNDIRECTED);

    // Create Window
    gv.createWindow(600, 600);

    Node &node12 = gv.getNode(12);
    Node &node13 = gv.getNode(13);

    bool i = false;

    while(gv.isWindowOpen()){

        Sleep(1000);

        gv.lock();
        node12.setPosition(i ? sf::Vector2f(250, 550) : sf::Vector2f(200, 550));
        node13.setPosition(i ? sf::Vector2f(350, 550) : sf::Vector2f(400, 550));
        gv.unlock();

        i = !i;
    }

    // Join viewer thread (blocks till window closed)
    gv.join();
}

