#include <iostream>
#include "Graph.hpp"



int main(){
    Graph someGraph;

    for (int i = 0; i < 127; ++i){
        for( int j = 0; j < 6; ++j){
            std::cout << someGraph.adjlist[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}

