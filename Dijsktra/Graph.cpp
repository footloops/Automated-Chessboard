#include <iostream>
#include "Graph.hpp"
#include "min_heap.hpp"
#include <limits.h>

void Graph::insertEdge(int OriginNodeId, int destNodeId, int distance, int origin_x_coord, int origin_y_coord, int dest_x_coord, int dest_y_coord)
{
    if (OriginNodeId == destNodeId){
        std::cout << "Failed to insert: Same Id" << std::endl;
        return;
    }

    if (this->adjListSize[OriginNodeId] == 6)
    {
        std::cout << "Failed to Insert: List full" << std::endl;
        return;
    }

    // Check if edge already exists
    for (int i = 0; i < 6; ++i){
        if (adjList[OriginNodeId][i].getNodeId() == destNodeId)
        {
            std::cout << "Failure to Insert: Edge Already exists" << std::endl;
            return;
        }
    }

    // Increasing numOfNodes counter
    if (adjListSize[OriginNodeId] == 0 && adjListSize[destNodeId] == 0)
    {
        this->numOfNodes = this->numOfNodes + 2;
    }
    if ( adjListSize[OriginNodeId] == 0 && adjListSize[destNodeId] != 0 || 
         adjListSize[OriginNodeId] != 0 && adjListSize[destNodeId] == 0){
        this->numOfNodes++;
    }

    this->adjList[OriginNodeId][this->adjListSize[OriginNodeId]] = Node(destNodeId, distance, dest_x_coord, dest_y_coord);
    this->adjListSize[OriginNodeId] = this->adjListSize[OriginNodeId] + 1;

    this->adjList[destNodeId][this->adjListSize[destNodeId]] = Node(OriginNodeId, distance, origin_x_coord, origin_x_coord);
    this->adjListSize[destNodeId] = this->adjListSize[destNodeId] + 1;

    return;
}

void Graph::dijkstra(int startingNode)
{
    // Initalize minHeap
    minHeap priorityQueue = minHeap(this->getnumOfNodes());

    this->shortestPathLen = 0; // Resetting value

    // Initally set all nodes in heap to distance inf
    for (int i = 0; i < this->numOfNodes; i++)
    {   
        this->distArray[i] = INT_MAX;
        this->prevArray[i] = -1;
        this->shortestPath[i] = -1;
        priorityQueue.heapInsert(i, 0, INT_MAX);
    }

    //Assign distance of zero to start node.
    priorityQueue.decreaseDistance(startingNode, 0);
    this->distArray[startingNode] = 0;

    priorityQueue.printHeap();

    //Visit all nodes whilst the heap is nonempty
    while (priorityQueue.getSize() != 0){
    
        minHeapNode minNode = priorityQueue.extractMin();
        // Visit all adjacent nodes
        for (int i = 0; i < this->adjListSize[minNode.getNodeId()]; ++i)
        {   
            // Make sure we are not visiting a "null" node
            if (this->adjList[minNode.getNodeId()][i].getNodeId() == -1){
                break;
            }

            // Decrease distance to all adjacent nodes according to edge weight (distance)
            int newDistance = this->adjList[minNode.getNodeId()][i].getDistance() + this->distArray[minNode.getNodeId()];
            //std::cout << this->adjList[minNode.getNodeId()][i].getDistance() << " " << newDistance << " " << minNode.getNodeId() << " " << this->distArray[minNode.getNodeId()] << std::endl;
            if (newDistance < distArray[this->adjList[minNode.getNodeId()][i].getNodeId()]){
                this->prevArray[this->adjList[minNode.getNodeId()][i].getNodeId()] = minNode.getNodeId();

                this->distArray[this->adjList[minNode.getNodeId()][i].getNodeId()] = this->adjList[minNode.getNodeId()][i].getDistance() + minNode.getDist();

                priorityQueue.decreaseDistance(this->adjList[minNode.getNodeId()][i].getNodeId(), newDistance);
            }
        }
        //priorityQueue.printHeap();
    }

    // for (int i = 0; i < getnumOfNodes(); i++){
    //     std::cout << this->prevArray[i] << " ";
    // }
    // std::cout << std::endl;

    return;
}

void Graph::findShortestPath(int startingNode, int endNode)
{
    dijkstra(startingNode);

    if (this->distArray[endNode] == INT_MAX){ // Making sure end node is actually reachable
        return;
    }

    for (int i = endNode; i != -1; i = prevArray[i]) // Iterating backwards. When reached -1, we are at starting node.
    {
        this->shortestPath[(this->getnumOfNodes() - 1) - this->shortestPathLen] = i; 
        this->shortestPathLen = this->shortestPathLen + 1;
    }

    

    return;
}

void Graph::print(int a)
{
    // Print adjacent vertices to vertex a
    for (int i = 0; i < 6; ++i)
    {
        std::cout << adjList[a][i].getNodeId() << " ";
    }
    std::cout << std::endl;

    return;
}

int Graph::getnumOfNodes()
{
    return this->numOfNodes;
}

int Graph::getShortestPathLen(){
    return this->shortestPathLen;
}

int main(){
    Graph graph = Graph();
    
    // graph.insertEdge(1, 2, 1, 0, 0, 40, 0);
    // graph.insertEdge(1, 3, 1, 0, 0, 80, 0);
    // graph.insertEdge(1, 4, 1, 0, 0, 120, 0);

    graph.insertEdge(0, 1, 4, 0, 0, 40, 0);
    graph.insertEdge(0, 2, 1, 0, 0, 80, 0);
    graph.insertEdge(1, 2, 2, 0, 0, 80, 0);
    graph.insertEdge(1, 3, 1, 0, 0, 160, 0);
    graph.insertEdge(2, 3, 5, 80, 0, 160, 0);
    graph.insertEdge(3, 4, 3, 160, 0, 240, 0);

    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 6; ++j){
            std::cout << graph.adjList[i][j].getNodeId() << " ";
        }
        std::cout << std::endl;
    }

    //std::cout << graph.getnumOfNodes() << std::endl;

    graph.findShortestPath(1, 3);

    std::cout << "Finished Calculating shortest Path" << std::endl;

    for (int i = graph.getnumOfNodes() - graph.getShortestPathLen(); i < graph.getnumOfNodes(); ++i)
    {
        std::cout << graph.shortestPath[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}