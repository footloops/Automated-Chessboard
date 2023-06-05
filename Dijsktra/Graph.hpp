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
        void setNodeAsOccupied(char column, short row);
        void setNodeAsEmpty(char column, short row);

        int getnumOfNodes();
        int getShortestPathLen();
        
        Node adjList[113][8]{};
        short adjListSize[113]{}; // Keeps track of each adjacency list size (the nested array)
        short shortestPath[113];   // Path of nodes to traverse to get from source node to destination node.
        unsigned int distArray[113]{}; // Track distance values from starting node
        short prevArray[113]{}; // Tracks the index of the node you took to get to some node i

    private:
        // Index of array will correspond to origin node. Nested array will contain adjacent nodes
        short shortestPathLen = 0;
        short numOfNodes = 0;
        //std::vector<minHeapNode> MSToutput = std::vector<minHeapNode>();
};

#endif