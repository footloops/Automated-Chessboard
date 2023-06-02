#include "min_heap.hpp"
#include <iostream>

minHeapNode::minHeapNode()
{
    this->nodeId = -1;
    this->distance = -1;
}

minHeapNode::minHeapNode(int origin, int distance)
{
    this->distance = distance; // Node value
    this->nodeId = origin;
}

minHeap::minHeap(int numOfNodes)
{
    this->numOfNodes = numOfNodes;
    this->array = new minHeapNode[numOfNodes];
    for (int i = 0; i < numOfNodes; ++i)
    {
        this->array[i] = minHeapNode();
    }
}

minHeap::~minHeap()
{
    delete[] this->array;
    this->array = nullptr;
}

void minHeap::Heapify(int i)
{
    int smallest = i;
    if (Left(i) < this->size && (this->array[Left(i)].distance < this->array[smallest].distance || this->array[i].distance == -1))
    {
        smallest = Left(i);
    }
    if (Right(i) < this->size && (this->array[Right(i)].distance < this->array[smallest].distance || this->array[smallest].distance == -1))
    {
        smallest = Right(i);
    }

    if (smallest != i )
    {
        minHeapNode temp = this->array[i];

        //Swapping nodes in heap
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
    if (this->array[parent(i)].distance > this->array[i].distance || this->array[parent(i)].getDist() == -1)
    {
        //swap
        minHeapNode temp = this->array[parent(i)];

        this->array[parent(i)] = this->array[i];
        this->array[i] = temp;

    }
    moveUp(parent(i));
}

void minHeap::heapInsert(int nodeId, int distance)
{   
    if (this->size > 127) {
        std::cout << "Inserted too many nodes" << std::endl;
        return;
    }

    this->array[this->size] = minHeapNode(nodeId, distance);

    moveUp(this->size);
    this->size = this->size + 1;

    return;
}

minHeapNode minHeap::extractMin()
{
    minHeapNode min = this->array[0];

    // Switch last entry and first entry
    this->array[0] = this->array[this->size-1];
    this->array[this->size-1] = min;

    // "Removing" last entry
    this->array[this->size-1] = minHeapNode(this->array[this->size-1].getNodeId(), -1);

    this->size = this->size - 1;

    Heapify(0);

    return min;
}

// Assumes newDistance value is always smaller than the current distance at node array[nodeId]
void minHeap::decreaseDistance(int nodeId, int newDistance)
{
    //Find Node
    int index = 0;
    for (int i = 0; i < this->numOfNodes; ++i)
    {
        if (this->array[i].getNodeId() == nodeId){
            index = i;
        }
    }

    this->array[index].distance = newDistance;

    moveUp(index);
    return;
}

void minHeap::printHeap()
{
    for (int i = 0; i < this->numOfNodes; i++)
    {
        std::cout << this->array[i].getNodeId() << " " << this->array[i].getDist() << std::endl;
    }
    std::cout << "Size of Minheap: " << this->size << std::endl;
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

int minHeapNode::getDist()
{
    return this->distance;
}

int minHeap::getNumofNodes()
{
    return this->numOfNodes;
}

// int main() {
//     minHeap heap = minHeap(127);
    
//     for (int i = 0; i < heap.getNumofNodes(); ++i){
//         heap.heapInsert(i, i+1, 1);
//         std::cout << heap.array[i].getNodeId() << " " << heap.array[i].getDestination() << " " << heap.array[i].getDist() << " " << (i-1)/2 << " | " << heap.pos[i] << std::endl;
//     }

//     std::cout << heap.getSize() << std::endl;

//     heap.decreaseDistance(126, 0);

//     for (int i = 0; i < heap.getNumofNodes(); ++i){
//         std::cout << heap.array[i].getNodeId() << " " << heap.array[i].getDestination() << " " << heap.array[i].getDist() << " " << (i-1)/2 << " | " << heap.pos[i] << std::endl;
//     }

//     return 0;
// }