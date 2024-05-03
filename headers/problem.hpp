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
        void userProblem();
        int getPuzzleSize();
        vector<node> getStartState();
        vector<node> getGoalState();
        void printStartState(); // for testing purposes
        void printGoalState();   // for testing purposes
        void UniformCostSearch();
        void MisplacedTileSearch(vector<node> x);
        void EuclideanDistanceSearch();
        bool GoalStateTest();

};

#endif