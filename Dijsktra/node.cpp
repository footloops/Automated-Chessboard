#include <iostream>
#include "Node.hpp"

Node::Node()
{
    this->nodeId = -1;
    this->distance = -1;
    this->x_coord = -1;
    this->y_coord = -1;
}

Node::Node(int nodeId, int distance, int x_coord, int y_coord)
{
    this->nodeId = nodeId;
    this->distance = distance;
    this->x_coord = x_coord;
    this->y_coord = y_coord;
}

int Node::getDistance()
{
    return this->distance;
}

int Node::getNodeId()
{
    return this->nodeId;
}

int Node::getxCoord(){
    return this->x_coord;
}

int Node::getyCoord(){
    return this->y_coord;
}