#include <iostream>
#include <cmath>
#include <queue>

#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    // start state
    int counter = 0;
    int tiles[9] = {1, 0, 3, 4, 2, 6, 7, 5, 8};
    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            puzzle.state[i][j] = tiles[counter];
            counter++;
        }
    }
}

void Problem::userProblem() {    // "constructor" based on user input
    int userInput = 0;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> userInput;
            puzzle.state[i][j] = userInput;
        }
    }
}

void Problem::printStartState() { // for testing purposes
    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            cout << puzzle.state[i][j] << " ";
        }
        cout << endl;
    }
}

bool Problem::GoalStateTest(node puzzleInput) {
    int counter = 1;

    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (puzzleInput.state[i][j] == counter) {
                counter++;
                continue;
            }
            else {
                if (counter == 9 && puzzleInput.state[i][j] == 0) {
                    continue;
                }
                return false;
            }
        }
    }
    
    return true;
}

double Problem::EuclideanDistanceSearch(node inputPuzzle){
    // maybe add goal state checker here
    if(GoalStateTest(inputPuzzle)){
        return 0;
    }

    int goalState[3][3] = {{1,2,3}, {4,5,6}, {7,8,0}};

    double heuristicCost = 0;

    for(int i = 0; i < puzzleSize; i++){
        for(int j = 0; j < puzzleSize; ++j){
            // see if the state is 0 or its equal to the goal state
            if(inputPuzzle.state[i][j]==0 || inputPuzzle.state[i][j] == goalState[i][j]){
                continue;
            }
            // if its misplaced
            // find how far each of the tiles are in the x and y
            // run equation (i - igoallocation)^2
            else{
                int igoallocation = 0;
                int jgoallocation = 0;

                for(int newi = 0; newi < puzzleSize; ++newi){
                    for(int newj = 0; newj < puzzleSize; ++newj){
                        if(inputPuzzle.state[i][j] == goalState[newi][newj]){
                            igoallocation = newi;
                            jgoallocation = newj;
                        }
                    }
                }
                heuristicCost += sqrt(pow(i-igoallocation, 2) + pow(j-igoallocation, 2));
            }
        }
    }

    return heuristicCost;
}

struct Compare { // helper for priority queue
    bool operator()(const node& a, const node& b){
        return (a.cost + a.heuristicCost) > (b.cost + b.heuristicCost);
    } // to use: priority_queue<node, vector<node>, Compare> pq;
};

bool Problem::canShiftUp(node inputPuzzle) {
    for (int i = 0; i < puzzleSize; i++) {
        for (int j = 0; j < puzzleSize; j++) {
            if (inputPuzzle.state[2][0] == 0) {  // cannot shift up if the 0 is in the bottom left corner
                return false;
            }

            if (inputPuzzle.state[2][1] == 0) { // cannot shift up if the 0 is in the bottom center
                return false;
            }
        
            if (inputPuzzle.state[2][1] == 0) { // cannot shift up if the 0 is in the bottom right corner
                return false;
            }
        }
    }

    return true;
}

bool Problem::canShiftDown(node inputPuzzle) {
    for (int i = 0; i < puzzleSize; i++) {
        for (int j = 0; j < puzzleSize; j++) {
            if (inputPuzzle.state[0][0] == 0) {  // cannot shift down if the 0 is in the upper left corner
                return false;
            }

            if (inputPuzzle.state[0][1] == 0) { // cannot shift down if the 0 is in the upper center
                return false;
            }
        
            if (inputPuzzle.state[0][2] == 0) { // cannot shift down if the 0 is in the upper right corner
                return false;
            }
        }
    }

    return true;
}

bool Problem::canShiftLeft(node inputPuzzle) {
    for (int i = 0; i < puzzleSize; i++) {
        for (int j = 0; j < puzzleSize; j++) {
            if (inputPuzzle.state[0][2] == 0) {  // cannot shift left if the 0 is in the rightmost column (upper corner)
                return false;
            }

            if (inputPuzzle.state[1][2] == 0) { // cannot shift left if the 0 is in the rightmost column (center)
                return false;
            }
        
            if (inputPuzzle.state[1][2] == 0) { // cannot shift left if the 0 is in the rightmost column (bottom corner)
                return false;
            }
        }
    }

    return true;
}

bool Problem::canShiftRight(node inputPuzzle) {
    for (int i = 0; i < puzzleSize; i++) {
        for (int j = 0; j < puzzleSize; j++) {
            if (inputPuzzle.state[0][0] == 0) {  // cannot shift right if the 0 is in the leftmost column (upper corner)
                return false;
            }

            if (inputPuzzle.state[1][0] == 0) { // cannot shift right if the 0 is in the leftmost column (center)
                return false;
            }
        
            if (inputPuzzle.state[1][0] == 0) { // cannot shift right if the 0 is in the leftmost column (bottom corner)
                return false;
            }
        }
    }

    return true;
}