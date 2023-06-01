#ifndef NODE_H
#define NODE_H

// Since using adjacent list, each node must store its number, and associated weight to its adjacent node.
class Node
{  
    public:
        Node();
        Node(int nodeId, int distance);
        int getNodeId();
        int getDistance();
        int getxCoord();
        int getyCoord();

    private:
        int nodeId;
        int x_coord;
        int y_coord;
        int distance;
};

#endif