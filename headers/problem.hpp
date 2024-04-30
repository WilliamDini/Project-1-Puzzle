#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <iostream>
#include "../headers/node.hpp"
using namespace std;

class Problem {
    protected:
        int puzzleSize = 9;
        vector<node> startState;
        vector<node> goalState;
        // int frontier[1];

    public:
        Problem();
        Problem(vector<node> startState);
        int getPuzzleSize();
        // void printStartState(); // for testing purposes
        // void printGoalState();   // for testing purposes
        void UniformCostSearch();
        void MisplacedTileSearch();
        void EuclideanDistanceSearch();
        bool GoalStateTest();

};

#endif