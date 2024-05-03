#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <iostream>
#include "../headers/node.hpp"
using namespace std;

class Problem {
    protected:
        Node puzzle;
        Node goalState;
        int puzzleSize = 3;
        // int frontier[1];

    public:
        Problem();
        void userProblem();
        // int getPuzzleSize(); // dont need this for now
        // vector<Node> getStartState(); // dont need this for now
        // vector<Node> getGoalState(); // dont need this for now
        void printState(); // for testing purposes
        // void printGoalState();   // for testing purposes
        void UniformCostSearch();
        void MisplacedTileSearch();
        double EuclideanDistanceSearch(vector<Node> startState);
        bool GoalStateTest();
        void swapUp();
        void swapLeft();
        void swapRight();
        void swapDown();
        pair<int, int> find(int, Node);
        int evaluate(int);

};

#endif