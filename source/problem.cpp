#include <iostream>
#include <cmath>
#include <queue>

#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    // start state
    int counter = 0;
    int tiles[9] = {1,2,3,4,5,6,7,8,0};
    // int tiles[9] = {8,3,4,5,2,6,7,1,0};
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            puzzle.state[i][j] = tiles[counter];
            counter++;
        }
    }
}

void Problem::userProblem() {    // "constructor" based on user input
    int userInput = 0;
    
    for (int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            cin >> userInput;
            puzzle.state[i][j] = userInput;
        }
    }
}

void Problem::printStartState() { // for testing purposes
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            cout << puzzle.state[i][j] << " ";
        }
        cout << endl;
    }
}


bool Problem::GoalStateTest(node puzzleInput) { // need to be fixed
    int counter = 1;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzleInput.state[i][j]==counter){
                counter++;
                continue;
            }
            else{
                if(counter == 9 && puzzleInput.state[i][j]==0){
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

struct Compare{ // helper for priority queue
    bool operator()(const node& a, const node& b){
        return (a.cost + a.heuristicCost) > (b.cost + b.heuristicCost);
    } // to use: priority_queue<node, vector<node>, Compare> pq;
};