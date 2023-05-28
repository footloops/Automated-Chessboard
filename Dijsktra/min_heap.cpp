#include "min_heap.hpp"
#include <iostream>

minHeapNode::minHeapNode()
{
    this->destination = -1;
    this->nodeId = -1;
    this->distance = -1;
}

minHeapNode::minHeapNode(int origin, int destination ,int distance)
{
    this->distance = distance; // Node value
    this->nodeId = origin;
    this->destination = destination;
}

minHeap::minHeap(int numOfNodes)
{
    this->numOfNodes = numOfNodes;
    this->pos = new int[numOfNodes];
    this->array = new minHeapNode[numOfNodes]{};
    for (int i = 0; i < 127; ++i)
    {
        this->pos[i] = -1;
    }
}

minHeap::~minHeap()
{
    delete[] this->pos;
    delete[] this->array;
}

void minHeap::Heapify(int i)
{
    int smallest = i;

    if (Left(i) <= this->size && this->array[Left(i)].distance < this->array[smallest].distance)
    {
        smallest = Left(i);
    }
    if (Right(i) <= this->size && this->array[Right(i)].distance < this->array[smallest].distance)
    {
        smallest = Right(i);
    }

    if (smallest != i)
    {
        minHeapNode temp = this->array[i];

        //Swapping nodes in heap
        this->pos[array[smallest].getNodeId()] = i;
        this->pos[array[i].getNodeId()] = smallest;

        this->array[i] = this->array[smallest];
        this->array[smallest] = temp;

        Heapify(smallest);
    }

    return;
}

void minHeap::moveUp(int i)
{
    // Reached top of tree
    if (i == 0 )
    {
        return;
    }
    if (this->array[parent(i)].distance > this->array[i].distance)
    {
        //swap
        minHeapNode temp = this->array[parent(i)];
        this->pos[array[parent(i)].getNodeId()] = i;
        this->pos[array[i].getNodeId()] = parent(i);

        this->array[parent(i)] = this->array[i];
        this->array[i] = temp;

    }
    moveUp(parent(i));
}

void minHeap::heapInsert(int nodeId, int destination, int distance)
{   
    if (this->size > 127) {
        std::cout << "Inserted too many nodes" << std::endl;
        return;
    }

    this->array[this->size] = minHeapNode(nodeId, destination, distance);
    this->pos[nodeId] = this->size; 

    moveUp(this->size);
    this->size = this->size + 1;

    return;
}

minHeapNode minHeap::extractMin()
{
    minHeapNode min = this->array[0];
    minHeapNode temp = this->array[0];


    // Switch last entry and first entry
    this->array[0] = this->array[this->size-1];
    this->array[this->size-1] = temp;

    this->pos[0] = this->pos[this->size-1];
    this->pos[temp.getNodeId()] = 0;

    // "Removing" last entry
    this->array[this->size-1] = minHeapNode();

    this->size = this->size - 1;

    Heapify(0);

    return min;
}

// Assumes newDistance value is always smaller than the current distance at node array[nodeId]
void minHeap::decreaseDistance(int nodeId, int newDistance)
{
    int index = this->pos[nodeId];

    //std::cout << index << std::endl;

    this->array[index].distance = newDistance;

    moveUp(index);
    return;
}

int minHeap::parent(int i)
{
    return ( (i-1)/2);
}

int minHeap::Left(int i)
{
    return (2*i + 1);
}

int minHeap::Right(int i)
{
    return (2*i + 2);
}

int minHeap::getSize()
{
    return this->size;
}

int minHeapNode::getNodeId()
{
    return this->nodeId;
}

int minHeapNode::getDestination()
{
    return this->destination;
}

int minHeapNode::getDist()
{
    return this->distance;
}

int minHeap::getNumofNodes()
{
    return this->numOfNodes;
}

int main() {
    minHeap heap = minHeap(127);
    
    for (int i = 0; i < heap.getNumofNodes(); ++i){
        heap.heapInsert(i, i+1, 1);
        std::cout << heap.array[i].getNodeId() << " " << heap.array[i].getDestination() << " " << heap.array[i].getDist() << " " << (i-1)/2 << " | " << heap.pos[i] << std::endl;
    }

    std::cout << heap.getSize() << std::endl;

    heap.decreaseDistance(126, 0);

    for (int i = 0; i < heap.getNumofNodes(); ++i){
        std::cout << heap.array[i].getNodeId() << " " << heap.array[i].getDestination() << " " << heap.array[i].getDist() << " " << (i-1)/2 << " | " << heap.pos[i] << std::endl;
    }

    return 0;
}