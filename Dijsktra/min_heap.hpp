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

class minHeapNodeV2
{
    public:
        minHeapNodeV2(int nodeId, int distance);
        int getNodeId();
        int getDist();

        minHeapNodeV2* p_getNextNode();
        void setNextNode(minHeapNodeV2* newNode);
    
    private:
        int nodeId;
        int distance;
        minHeapNodeV2* p_nextNode;

    friend class minHeapV2;
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

class minHeapV2
{
    public:
        minHeapV2(const int capacity);
        ~minHeapV2();

        int parent(int i);
        int Left(int i);
        int Right(int i);

        void Heapify(int i);
        void heapInsert(int const nodeId, int const distance);
        minHeapNodeV2* extractMin();
        void decreaseDistance(int nodeId, int newDistance);

        void moveUp(int i);
        
        int getSize();
        int getNumofNodes();
        void printHeap();

    private:
        int capacity;
        minHeapNodeV2* p_list_head;
        int numOfNodes;

        friend class Graph;
};


#endif