#ifndef MIN_HEAP_H
#define MIN_HEAP_H

class minHeapNode
{   
    public:
        minHeapNode();
        minHeapNode(int origin, int weight);
        int getNodeId();
        int getDist();
    
    private:
        int nodeId;
        int distance;

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
        void heapInsert(int nodeId, int distance);
        minHeapNode extractMin();
        void decreaseDistance(int nodeId, int newDistance);

        void moveUp(int i);
        
        int getSize();
        int getNumofNodes();
        void printHeap();

    private:
        int size = 0;
        int *pos; // Position of some node in heap. Index maps to some nodeId. Int at location is location of node within heap array.
        minHeapNode *array;
        int numOfNodes;

        friend class Graph;
};


#endif