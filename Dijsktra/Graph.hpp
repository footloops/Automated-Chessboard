#ifndef GRAPH_H
#define GRAPH_H
#include "Node.hpp"

class Graph
{
    public:
        Graph();
        void insertEdge(int nodeId, int destNodeId, int distance);
        void print(int a);
        void dijkstra(int startingNode);
        void findShortestPath(int startingNode, int endNode);
        void setNodeAsOcupied(int nodeId);

        int getnumOfNodes();
        int getShortestPathLen();
        
        Node adjList[64][8]{};
        int adjListSize[64]{}; // Keeps track of each adjacency list size (the nested array)
        int shortestPath[64];   // Path of nodes to traverse to get from source node to destination node.
        int distArray[64]{}; // Track distance values from starting node
        int prevArray[64]{}; // Tracks the index of the node you took to get to some node i

    private:
        // Index of array will correspond to origin node. Nested array will contain adjacent nodes
        int shortestPathLen = 0;
        int numOfNodes = 0;
        //std::vector<minHeapNode> MSToutput = std::vector<minHeapNode>();
};

#endif