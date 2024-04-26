#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

struct node{
    int uniformCost = 0;
    int heuristicCost = 0;

    node *p = NULL;
};


#endif