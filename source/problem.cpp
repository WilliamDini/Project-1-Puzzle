#include <iostream>
#include <cmath>

#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    // start state
    int counter = 0;
    int tiles[9] = {1,3,4,5,2,6,7,8,0};
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

void Problem::printState() { // for testing purposes
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            cout << puzzle.state[i][j] << " ";
        }
        cout << endl;
    }
}


bool Problem::GoalStateTest() { // need to be fixed

    int counter = 1;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzle.state[i][j]==counter){
                counter++;
                continue;
            }
            else{
                if(counter == 9 && puzzle.state[i][j]==0){
                    continue;
                }
                return false;
            }
        }
    }
    
    return true;
}

void Problem::swapUp(pair<int, int> blankPos) {
    if (blankPos.second == 0) {
        cout << "ERROR: the algorithm is attempting to swap up when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second] = puzzle.state[blankPos.first][blankPos.second-1];
    puzzle.state[blankPos.first][blankPos.second-1] = 0;
}

void Problem::swapDown(pair<int, int> blankPos) {
    if(blankPos.second == 2) {
        cout << "ERROR: the algorithm is attempting to swap down when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second] = puzzle.state[blankPos.first][blankPos.second+1];
    puzzle.state[blankPos.first][blankPos.second+1] = 0;
}

void Problem::swapLeft(pair<int, int> blankPos) {
    if(blankPos.first == 0) {
        cout << "ERROR: the algorithm is attempting to swap left when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second] = puzzle.state[blankPos.first-1][blankPos.second];
    puzzle.state[blankPos.first-1][blankPos.second] = 0;
}

void Problem::swapRight(pair<int, int> blankPos) {
    if(blankPos.first == 2) {
        cout << "ERROR: the algorithm is attempting to swap right when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second] = puzzle.state[blankPos.first+1][blankPos.second];
    puzzle.state[blankPos.first+1][blankPos.second] = 0;
}

  
// double Problem::EuclideanDistanceSearch(vector<node> startState){
//     // maybe add goal state checker here

//     // first change states into a 2d vector and create a goals 2d vector
//     vector<vector<node>> tempStates(3, vector<node>(3));
//     vector<vector<int> > tempGoals = {{1,2,3}, {4,5,6}, {7,8,0}};

//     // push the states into the new states vector
//     int startcounter = 0;
//     for(int i = 0; i < 3; i++){
//         for(int j = 0; j < 3; j++){
//             tempStates[i].push_back(startState.at(startcounter));
//             startcounter++;
//         }
//     }

//     double heuristicCost = 0;

//     for(int i = 0; i < tempStates.size(); i++){
//         for(int j = 0; j < tempStates[i].size(); j++){
//             // if the state is 0 or its equal to goal state: continue
//             if(tempStates[i][j].state == 0 || tempStates[i][j].state == tempGoals[i][j]){ 
//                 continue;
//             }

//             // if its misplaced 
//             // find how far each of the titles are in the x and y 
//             // run equation (i - igoallocation)^2...
//             else{
//                 int igoallocation = 0;
//                 int jgoallocation = 0;

//                 // find the i and j of the goal state
//                 for(int newi = 0; newi < tempStates.size(); newi++){
//                     for(int newj = 0; newj < tempStates[newi].size(); newj++){
//                         if(tempStates[i][j].state == tempGoals[newi][newj]){
//                             igoallocation = newi;
//                             jgoallocation = newj;
//                         }
//                     }
//                 }

//                 heuristicCost += sqrt(pow(i-igoallocation, 2) + pow(j-igoallocation, 2));
//             }
//         }
//     }

//     return heuristicCost;
// }