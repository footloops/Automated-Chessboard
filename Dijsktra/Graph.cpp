#include <iostream>
#include "Graph.hpp"
#include "min_heap.hpp"
#include <limits.h>

// // Assuming 113 Nodes (1 node in center of tile, and 4 nodes on each corner of tile. No nodes on edges of chessboard)
Graph::Graph()
{
    int counter = 0;
    for (int y = 0; y < 8; y++){
        for (int x = 0; x < 8; x++){
            // Setting default chess tiles to occupied.
            if ( y < 2 || y > 5){
                this->setNodeAsOccupied( 72 - x, 8-y );
                //std::cout << char(72 - x) << " " << 8 - y << std::endl;
            }

            // Horizontal edges
            if (x < 7){
                this->insertEdge(counter, counter + 1, 1);
                if (x < 6){
                    if (counter + 9 < 113){
                        this->insertEdge(counter + 8, counter + 9, 2);
                    }
                }
            }

            // Vertical corner node connections
            if ( y < 7 ){
                if (counter + 23 < 113){
                    this->insertEdge(counter + 8, counter + 23, 2);
                }   
            }

            // Vertical Edges
            if (counter + 15 < 113){
                this->insertEdge(counter, counter + 15, 1);
            }
            
            //Diagonals
            if ( y < 7 && x < 7){
                // Topright
                this->insertEdge(counter, counter + 8, 1);
                //Topleft
                this->insertEdge(counter+1, counter + 8, 1);
                if (counter + 15 < 113){
                    // Bottomright
                    this->insertEdge(counter+15, counter + 8, 1);
                    this->insertEdge(counter+16, counter + 8, 1);
                }
            }

            counter++;
        }
        counter = counter + 7;
    }
}

void Graph::insertEdge(int OriginNodeId, int destNodeId, int distance)
{
    if (OriginNodeId == destNodeId){
        std::cout << "Failed to insert: Same Id" << std::endl;
        return;
    }

    if (this->adjListSize[OriginNodeId] == 8)
    {
        std::cout << "Failed to Insert: List full" << std::endl;
        return;
    }

    // // Check if edge already exists
    // for (int i = 0; i < 8; ++i){
    //     if (adjList[OriginNodeId][i].getNodeId() == destNodeId)
    //     {
    //         std::cout << "Failure to Insert: Edge Already exists" << std::endl;
    //         return;
    //     }
    // }

    // Increasing numOfNodes counter
    if (adjListSize[OriginNodeId] == 0 && adjListSize[destNodeId] == 0)
    {
        this->numOfNodes = this->numOfNodes + 2;
    }
    if ( adjListSize[OriginNodeId] == 0 && adjListSize[destNodeId] != 0 || 
         adjListSize[OriginNodeId] != 0 && adjListSize[destNodeId] == 0){
        this->numOfNodes++;
    }

    this->adjList[OriginNodeId][this->adjListSize[OriginNodeId]] = Node(destNodeId, distance);
    this->adjListSize[OriginNodeId] = this->adjListSize[OriginNodeId] + 1;

    this->adjList[destNodeId][this->adjListSize[destNodeId]] = Node(OriginNodeId, distance);
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
        this->distArray[i] = SHRT_MAX;
        this->prevArray[i] = -1;
        this->shortestPath[i] = -1;
        priorityQueue.heapInsert(i, SHRT_MAX);
    }

    //Assign distance of zero to start node.
    priorityQueue.decreaseDistance(startingNode, 0);
    this->distArray[startingNode] = 0;

    //priorityQueue.printHeap();

    //Visit all nodes whilst the heap is nonempty
    while (priorityQueue.getSize() != 0){ 
        minHeapNode minNode = priorityQueue.extractMin();

        // priorityQueue.printHeap();
        // std::cout << "---------" << std::endl;
        
        // Visit all adjacent nodes
        for (int i = 0; i < this->adjListSize[minNode.getNodeId()]; ++i)
        {   
            // Make sure we are not visiting a "null" node
            if (this->adjList[minNode.getNodeId()][i].getNodeId() == -1){
                break;
            }

            // Decrease distance to all adjacent nodes according to edge weight (distance)
            unsigned int newDistance = this->adjList[minNode.getNodeId()][i].getDistance() + this->distArray[minNode.getNodeId()];
            if (newDistance < distArray[this->adjList[minNode.getNodeId()][i].getNodeId()]){
                this->prevArray[this->adjList[minNode.getNodeId()][i].getNodeId()] = minNode.getNodeId();

                this->distArray[this->adjList[minNode.getNodeId()][i].getNodeId()] = this->adjList[minNode.getNodeId()][i].getDistance() + minNode.getDist();

                priorityQueue.decreaseDistance(this->adjList[minNode.getNodeId()][i].getNodeId(), newDistance);
            }
        }
        //priorityQueue.printHeap();
    }

    return;
}

void Graph::findShortestPath(int startingNode, int endNode)
{
    dijkstra(startingNode);

    if (this->distArray[endNode] == SHRT_MAX){ // Making sure end node is actually reachable
        std::cout << "Cannot compute shortest path: End node is occupied" << std::endl;
        return;
    }

    for (int i = endNode; i != -1; i = prevArray[i]) // Iterating backwards. When reached -1, we are at starting node.
    {   
        this->shortestPath[(this->getnumOfNodes() - 1) - this->shortestPathLen] = i; 
        this->shortestPathLen = this->shortestPathLen + 1;
    }

    return;
}

void Graph::setNodeAsOccupied(char column, short row)
{
    // Determining Node id based on column and row.
    // Converting column char to an integer representation
    short columnNum = 72 - int(column);
    row = 15 * (8 - row);
    short nodeId = columnNum + row;
    std::cout << nodeId << std::endl;

    for (int i = 0; i < this->adjListSize[nodeId]; ++i){
        this->adjList[nodeId][i].distance = SHRT_MAX;

        for (int j = 0; j < this->adjListSize[adjList[nodeId][i].getNodeId()]; j++){
            if (this->adjList[adjList[nodeId][i].getNodeId()][j].getNodeId() == nodeId){
                this->adjList[adjList[nodeId][i].getNodeId()][j].distance = SHRT_MAX;
            }
        }
    }

    return;
}

void Graph::setNodeAsEmpty(char column, short row)
{
    short columnNum = 72 - int(column);
    row = 15 * (8 - row);
    short nodeId = columnNum + row;

    for (int i = 0; i < this->adjListSize[nodeId]; ++i){
        this->adjList[nodeId][i].distance = 1;

        for (int j = 0; j < this->adjListSize[adjList[nodeId][i].getNodeId()]; j++){
            if (this->adjList[adjList[nodeId][i].getNodeId()][j].getNodeId() == nodeId){
                this->adjList[adjList[nodeId][i].getNodeId()][j].distance = 1;
            }
        }
    }

    return;
}

void Graph::print(int nodeId)
{
    // Print adjacent vertices to vertex a
    for (int i = 0; i < this->adjListSize[nodeId]; ++i)
    {
        std::cout << this->adjList[nodeId][i].getNodeId() << " ";
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

// int main(){
//     Graph graph = Graph();

//     for (int i = 0; i < 113; ++i){
//         std::cout << i << " | ";
//         for (int j = 0; j < 8; ++j){
//             std::cout << graph.adjList[i][j].getNodeId() << " " << graph.adjList[i][j].getDistance() << " | ";
//         }
//         std::cout << std::endl;
//     }

//     //graph.setNodeAsOccupied('F', 1);
//     //graph.setNodeAsOcupied(8);

//     // for (int i = 0; i < 113; ++i){
//     //     std::cout << i << " | ";
//     //     for (int j = 0; j < 8; ++j){
//     //         std::cout << graph.adjList[i][j].getNodeId() << " " << graph.adjList[i][j].getDistance() << " | ";
//     //     }
//     //     std::cout << std::endl;
//     // }

//     // graph.findShortestPath(0, 24);
//     // for (int i = graph.getnumOfNodes() - graph.getShortestPathLen(); i < graph.getnumOfNodes(); ++i)
//     // {
//     //     std::cout << graph.shortestPath[i] << " ";
//     // }
//     // std::cout << std::endl;

//     return 0;
// }