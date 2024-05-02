#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <iostream>
#include "../headers/node.hpp"
using namespace std;

class Problem {
    protected:
        node puzzle;
        int puzzleSize = 3;
        // int frontier[1];

    public:
        Problem();
        void userProblem();
        // int getPuzzleSize(); // dont need this for now
        // vector<node> getStartState(); // dont need this for now
        // vector<node> getGoalState(); // dont need this for now
        void printStartState(); // for testing purposes
        // void printGoalState();   // for testing purposes
        void UniformCostSearch();
        void MisplacedTileSearch();
        double EuclideanDistanceSearch(vector<node> startState);
        bool GoalStateTest();

};

#endif