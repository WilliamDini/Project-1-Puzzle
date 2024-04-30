#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

struct node{
    vector<vector<int>> state;
    int cost = 0;
    int heuristicCost = 0;
    node *p = NULL;
};


#endif