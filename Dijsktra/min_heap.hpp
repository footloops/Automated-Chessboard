#ifndef MIN_HEAP_H
#define MIN_HEAP_H

class minHeapNode
{   
    public:
        minHeapNode();
        minHeapNode(int origin, int weight);
        short getNodeId();
        short getDist();
    
    private:
        short nodeId;
        unsigned int distance;

    friend class minHeap;
    friend class Graph;
};

class minHeap
{
    public:
        minHeap(int numOfNodes);
        ~minHeap();

        short parent(int i);
        short Left(int i);
        short Right(int i);

        void Heapify(int i);
        void heapInsert(int nodeId, int distance);
        minHeapNode extractMin();
        void decreaseDistance(int nodeId, int newDistance);

        void moveUp(int i);
        
        short getSize();
        short getNumofNodes();
        void printHeap();

    private:
        short size = 0;
        minHeapNode *array;
        short numOfNodes;

        friend class Graph;
};

#endif