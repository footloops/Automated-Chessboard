#ifndef GRAPH_H
#define GRAPH_H
#include "Node.hpp"

class Graph
{
    public:
        //Graph();
        void insertEdge(int nodeId, int destNodeId, int distance);
        void print(int a);
        void dijkstra(int startingNode);
        void findShortestPath(int startingNode, int endNode);

        int getnumOfNodes();
        int getShortestPathLen();
        
        Node adjList[8][6]{};
        int adjListSize[8]{}; // Keeps track of each adjacency list size (the nested array)
        int shortestPath[8];   // Path of nodes to traverse to get from source node to destination node.
        int distArray[8]{}; // Track distance values from starting node
        int prevArray[8]{}; // Tracks the index of the node you took to get to some node i

    private:
        // Index of array will correspond to origin node. Nested array will contain adjacent nodes
        int shortestPathLen = 0;
        int numOfNodes = 0;
        //Node **adjlist[127][6];
        //std::vector<minHeapNode> MSToutput = std::vector<minHeapNode>();
};

#endif