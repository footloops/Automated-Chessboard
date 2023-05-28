#ifndef NODE_H
#define NODE_H

// Since using adjacent list, each node must store its number, and associated weight to its adjacent node.
class Node
{  
    public:
        Node(int nodeId, int weight, int x_coord, int y_coord);
        int getnodeId();
        int getWeight();
        int getxCoord();
        int getyCoord();

    private:
        int nodeId;
        int x_coord;
        int y_coord;
        int weight;
};

#endif