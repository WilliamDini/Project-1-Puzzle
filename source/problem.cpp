#include <iostream>
#include <cmath>

#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    // goal state
    int counter = 0;
    int goal[9] = {
        1,2,3,
        4,5,6,
        7,8,0
    };
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            goalState.state[i][j].first = goal[counter];
            counter++;
        }
    }

    //default start state
    int tiles[9] = {
        1,3,4,
        5,2,6,
        7,8,0
        };
    counter = 0;
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            puzzle.state[i][j].first = tiles[counter];
            counter++;
        }
    }
}

void Problem::userProblem() {    // "constructor" based on user input
    int userInput = 0;
    
    for (int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            cin >> userInput;
            puzzle.state[i][j].first = userInput;
        }
    }
}

//changed to print state whenever we want
void Problem::printState() { // for testing purposes
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            cout << puzzle.state[i][j].first << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}


bool Problem::GoalStateTest() { // need to be fixed

    int counter = 1;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzle.state[i][j].first == counter){
                counter++;
                continue;
            }
            else{
                if(counter == 9 && puzzle.state[i][j].first == 0){
                    continue;
                }
                return false;
            }
        }
    }
    
    return true;
}

void Problem::swapLeft() {
    pair<int, int> blankPos(find(0, puzzle));
    if (blankPos.second == 0) {
        cout << "ERROR: the algorithm is attempting to swap left when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second].first = puzzle.state[blankPos.first][blankPos.second-1].first;
    puzzle.state[blankPos.first][blankPos.second-1].first = 0;
}

void Problem::swapRight() {
    pair<int, int> blankPos(find(0, puzzle));
    if(blankPos.second == 2) {
        cout << "ERROR: the algorithm is attempting to swap right when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second].first = puzzle.state[blankPos.first][blankPos.second+1].first;
    puzzle.state[blankPos.first][blankPos.second+1].first = 0;
}

void Problem::swapUp() {
    pair<int, int> blankPos(find(0, puzzle));
    if(blankPos.first == 0) {
        cout << "ERROR: the algorithm is attempting to swap up when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second].first = puzzle.state[blankPos.first-1][blankPos.second].first;
    puzzle.state[blankPos.first-1][blankPos.second].first = 0;
}

void Problem::swapDown() {
    pair<int, int> blankPos(find(0, puzzle));
    if(blankPos.first == 2) {
        cout << "ERROR: the algorithm is attempting to swap down when this is not possible.\n";
        return;
    }
    puzzle.state[blankPos.first][blankPos.second].first = puzzle.state[blankPos.first+1][blankPos.second].first;
    puzzle.state[blankPos.first+1][blankPos.second].first = 0;
}

//function used to evaluate the cost of a given number to the position it should be in
int Problem::evaluate(int number) {
    //finds the position in the 2d array that the number should be in via goal state
    pair<int, int> targetPos = find(number, goalState);
    //this is here so the items in the 0 column don't go to -1 and break, no idea if this works for problems over size 9
    if (targetPos.second == -1) { targetPos.second == 0; }
    
    //if the number is in the correct position, skip the search
    if (puzzle.state[targetPos.first][targetPos.second].first == goalState.state[targetPos.first][targetPos.second].first) {
        return 0;
    }
    else {
        for(int i = 0; i < puzzleSize; i++) {
            for(int j = 0; j < puzzleSize; j++) {
                //once correct position is found, calculate the distance
                if (goalState.state[i][j].first == number) {
                    return (abs(i-targetPos.first) + abs(j-targetPos.second));
                }
            }
        }
    }
    //this is just here so the compiler doesn't yell at me, we should never ever get here i hope
    return -1;
}

//function designed to find the coordinates of a number within the matrix
pair<int, int> Problem::find(int target, Node nodeToSearch) {
    for(int i = 0; i < puzzleSize; i++) {
        for(int j = 0; j < puzzleSize; j++) {
            if(puzzle.state[i][j].first == target) {
                pair<int, int> ret(i,j);
                return ret;
            }
        }
    }
    //here so compiler doesn't yell - should never get here if matrix was set up properly, i think?
    pair<int, int> ret(-1, -1);
    return ret;
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