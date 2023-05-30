#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Node.hpp"

class Graph
{
    public:
        void insertEdge(int nodeId, int destNodeId, int distance, int origin_x_coord, int origin_y_coord, int dest_x_coord, int dest_y_coord);
        void print(int a);
        void dijkstra(int startingNode);
        void findShortestPath(int startingNode, int endNode);

        int getnumOfNodes();
        
        Node adjList[5][6]{};
        int adjListSize[5]{}; // Keeps track of each adjacency list size (the nested array)
        int shortestPath[5];   // Path of nodes to traverse to get from source node to destination node
        int distArray[5]{}; // Track distance values from starting node
        int prevArray[5]{}; // Tracks the index of the node you took to get to some node i

    private:
        // Index of array will correspond to origin node. Nested array will contain adjacent nodes
        int numOfNodes = 0;
        //Node **adjlist[127][6];
        //std::vector<minHeapNode> MSToutput = std::vector<minHeapNode>();
};

#endif