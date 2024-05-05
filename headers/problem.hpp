#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <iostream>
#include "../headers/node.hpp"
using namespace std;

class Problem {
    protected:
        int puzzleSize = 3;
        int maxInQueue = 0;
        int numExpanded = 0;

    public:
        node puzzle;
        Problem();
        void userProblem();
        int getPuzzleSize();
        void printStartState();
        void printState(node puzzleInput);
        int getMaxInQueue();
        int getMaxExpanded();

        node uniformCostSearch(int whichHeuristic);
        int MisplacedTileSearch(node inputPuzzle);
        double EuclideanDistanceSearch(node inputPuzzle);

        bool GoalStateTest(node puzzleInput);
  
        bool canShiftUp(node inputPuzzle);
        bool canShiftDown(node inputPuzzle);
        bool canShiftLeft(node inputPuzzle);
        bool canShiftRight(node inputPuzzle);
  
        node shiftLeft(node puzzleInput);
        node shiftRight(node puzzleInput);
        node shiftUp(node puzzleInput);
        node shiftDown(node puzzleInput);

};

#endif