#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <iostream>
using namespace std;

class Problem {
    protected:
        int puzzleSize = 8;
        int startState[1];
        int goalState[1];

        Problem();
        void goLeft();
        void goRight();
        void goUp();
        void goDown();

};

#endif