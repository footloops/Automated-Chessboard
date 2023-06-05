#include <iostream>
#include "Node.hpp"

Node::Node()
{
    this->nodeId = -1;
    this->distance = -1;

}

Node::Node(int nodeId, int distance)
{
    this->nodeId = nodeId;
    this->distance = distance;
}

short Node::getDistance()
{
    return this->distance;
}

short Node::getNodeId()
{
    return this->nodeId;
}