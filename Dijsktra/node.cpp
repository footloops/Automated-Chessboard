#include <iostream>
#include "node.hpp"

Node::Node(int nodeId, int weight, int x_coord, int y_coord)
{
    this->nodeId = nodeId;
    this->weight = weight;
    this->x_coord = x_coord;
    this->y_coord = y_coord;
}

int Node::getWeight()
{
    return this->weight;
}

int Node::getnodeId()
{
    return this->nodeId;
}

int Node::getxCoord(){
    return this->x_coord;
}

int Node::getyCoord(){
    return this->y_coord;
}