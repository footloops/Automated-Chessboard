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
        void setNodeAsEmpty(int nodeId);

        int getnumOfNodes();
        int getShortestPathLen();
        
        Node adjList[64][8]{};
        short adjListSize[64]{}; // Keeps track of each adjacency list size (the nested array)
        short shortestPath[64];   // Path of nodes to traverse to get from source node to destination node.
        unsigned short distArray[64]{}; // Track distance values from starting node
        short prevArray[64]{}; // Tracks the index of the node you took to get to some node i

    private:
        // Index of array will correspond to origin node. Nested array will contain adjacent nodes
        short shortestPathLen = 0;
        short numOfNodes = 0;
        //std::vector<minHeapNode> MSToutput = std::vector<minHeapNode>();
};

#endif