#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>

class minHeapNode
{   
    public:
        minHeapNode();
        minHeapNode(int origin, int destination ,int weight);
        int getNodeId();
        int getDist();
        int getDestination();
    
    private:
        int nodeId;
        int distance;
        int destination;

    friend class minHeap;
    friend class Graph;
};

class minHeap
{
    public:
        minHeap(int numOfNodes);
        ~minHeap();

        int parent(int i);
        int Left(int i);
        int Right(int i);

        void Heapify(int i);
        void heapInsert(int stationNum, int destination, int distance);
        minHeapNode extractMin();
        void decreaseDistance(int nodeId, int newDistance);

        void moveUp(int i);

        int getSize();
        int getNumofNodes();

        int *pos; // Position of some node in heap. Index maps to some nodeId. Int at location is location of node within heap array.
        minHeapNode *array;

    private:
        int size = 0;
        // int pos[127]; // Position of some node in heap. Index maps to some nodeId. Int at location is location of node within heap array.
        // minHeapNode array[127]{};
        int numOfNodes;

        friend class Graph;
};


#endif