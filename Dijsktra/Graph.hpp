#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "node.hpp"

class Graph
{
    public:
        Graph();
        void load(int origin, int destination, int weight);
        int insertEdge(int origin, int destination, int weight);
        void print(int a);

        void setNumVertices(int x);
        int getNumVertices();
        int getNumOfEdges();

        Node *adjlist[127][6]{};

    private:
        // Index of array will correspond to origin node. Nested array will contain adjacent nodes
        //Node **adjlist[127][6];
        //std::vector<minHeapNode> MSToutput = std::vector<minHeapNode>();
};

#endif