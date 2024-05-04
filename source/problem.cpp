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

node Problem::shiftLeft(node puzzleInput) {
    if(!canShiftLeft(puzzleInput)){
        return;
    }

    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzleInput.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    int holder = puzzleInput.state[ilocation][jlocation-1];
    puzzleInput.state[ilocation][jlocation-1] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}

node Problem::shiftRight(node puzzleInput){
    if(!canShiftRight(puzzleInput)){
        return;
    }

    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzleInput.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    int holder = puzzleInput.state[ilocation][jlocation+1];
    puzzleInput.state[ilocation][jlocation+1] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}

node Problem::shiftUp(node puzzleInput){
    if(!canShiftUp(puzzleInput)){
        return;
    }

    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzleInput.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    int holder = puzzleInput.state[ilocation-1][jlocation];
    puzzleInput.state[ilocation-1][jlocation] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}

node Problem::shiftDown(node puzzleInput){
    if(!canShiftDown(puzzleInput)){
        return;
    }

    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(puzzleInput.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    int holder = puzzleInput.state[ilocation+1][jlocation];
    puzzleInput.state[ilocation+1][jlocation] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}
  
double Problem::EuclideanDistanceSearch(node puzzleInput){
    // maybe add goal state checker here
    if(GoalStateTest(puzzleInput)){
        return 0;
    }

    int goalState[3][3] = {{1,2,3}, {4,5,6}, {7,8,0}};

    double heuristicCost = 0;

    for(int i = 0; i < puzzleSize; i++){
        for(int j = 0; j < puzzleSize; ++j){
            // see if the state is 0 or its equal to the goal state
            if(puzzleInput.state[i][j]==0 || puzzleInput.state[i][j] == goalState[i][j]){
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
                        if(puzzleInput.state[i][j] == goalState[newi][newj]){
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


vector<node> Problem::expand(const node& puzzleInput) {
    vector<node> successors;

    int emptyTileRow = -1;
    int emptyTileCol = -1;
    for (int i = 0; i < puzzleSize; ++i) {
        for (int j = 0; j < puzzleSize; ++j) {
            if (puzzleInput.state[i][j] == 0) {
                emptyTileRow = i;
                emptyTileCol = j;
                break;
            }
        }
    }

    if (emptyTileRow > 0) {
        node successor = puzzleInput;
        swap(successor.state[emptyTileRow][emptyTileCol], successor.state[emptyTileRow - 1][emptyTileCol]);
        successors.push_back(successor);
    }
    if (emptyTileRow < puzzleSize - 1) {
        Node successor = puzzleInput;
        swap(successor.state[emptyTileRow][emptyTileCol], successor.state[emptyTileRow + 1][emptyTileCol]);
        successors.push_back(successor);
    }
    if (emptyTileCol > 0) {
        Node successor = puzzleInput;
        swap(successor.state[emptyTileRow][emptyTileCol], successor.state[emptyTileRow][emptyTileCol - 1]);
        successors.push_back(successor);
    }
    if (emptyTileCol < puzzleSize - 1) {
        Node successor = puzzleInput;
        swap(successor.state[emptyTileRow][emptyTileCol], successor.state[emptyTileRow][emptyTileCol + 1]);
        successors.push_back(successor);
    }

    return successors;
}

node Problem::uniformCostSearch(const node& initialNode){
    queue<node> nodes;
    nodes.push({initialNode});

    while(!node.empty()){

        node current_node = node.front();
        nodes.pop();

        if(goalTest(current_node.state)){
            cout << "A soultion is found!" << endl;
            return current_node;
        }
        vector<node> successors = expand(current_node);
        for(const suato& successors : successors){
            node.push(successor);
        }
    }
    cout << "No solution is found!" << endl;
    return node();

}

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