#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_set>

#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    // start state
    int counter = 0;
    int tiles[9] = {1,2,3,4,8,0,7,6,5};
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

int Problem::getPuzzleSize() {
    return puzzleSize;
}

void Problem::printStartState() {
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            cout << puzzle.state[i][j] << " ";
        }
        cout << endl;
    }
}

void Problem::printState(node puzzleInput){
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            cout << puzzleInput.state[i][j] << " ";
        }
        cout << endl;
    }
}

bool Problem::GoalStateTest(node puzzleInput) {
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

bool Problem::canShiftUp(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(inputPuzzle.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(ilocation==0){
        return false;
    }
    return true;
}

bool Problem::canShiftDown(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(inputPuzzle.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(ilocation==2){
        return false;
    }
    return true;
}

bool Problem::canShiftLeft(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(inputPuzzle.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(jlocation==0){
        return false;
    }
    return true;
}

bool Problem::canShiftRight(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j){
            if(inputPuzzle.state[i][j]==0){
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(jlocation==2){
        return false;
    }
    return true;
}

node Problem::shiftLeft(node puzzleInput) {
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

int Problem::MisplacedTileSearch(node inputPuzzle) {
    if(GoalStateTest(inputPuzzle)) {
        return 0;
    }

    int goalS[3][3] = {{1,2,3}, {4,5,6}, {7,8,0}};

    int heuCount = 0;
    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            if(inputPuzzle.state[i][j] != goalS[i][j]) {
                heuCount++;
            }
        }
    }
    return heuCount;
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
        return (a.cost + a.heuristicCost) > (b.cost + b.heuristicCost); // places the lowest cost at the top of the priority queue
    } 
};

struct hashFunction{ // helper for the hashtable 
    size_t operator()(const vector<int> &myVector) const{ 
    hash<int> hasher; 
    size_t answer = 0; 
      
    for (int i : myVector){ 
        answer ^= hasher(i) + 0x9e3779b9 + (answer << 6) + (answer >> 2); 
    } 
    return answer; 
    } 
}; 

node Problem::uniformCostSearch(int whichHeuristic){
    if(GoalStateTest(puzzle)){
        cout << "Already Solved" << endl;
        return puzzle;
    }

    if(whichHeuristic == 2){
        cout << "Using Misplaced Tile Heuristic" << endl;
    }
    else if(whichHeuristic == 3){
        cout << "Using Euclidean Distance Heuristic" << endl;
    }
    else{
        cout << "Using Uniform Cost Search" << endl;
    }

    // priority queue for the nodes which chooses the node with the lowest cost + heuristic cost
    priority_queue<node, vector<node>, Compare> pqueue; 
    // hash map to make sure that states that have already been visited arent visited again
    unordered_set<vector<int>, hashFunction> hash;
    vector<int> checkIfVisited;

    pqueue.push(puzzle);

    while(!pqueue.empty()){
        node top = pqueue.top();
        pqueue.pop();

        if(GoalStateTest(top)){
            return top;
        }

        // add the state into a vector so that we can put it into the hashmap and check if it was visited
        checkIfVisited.clear();
        for(int i = 0; i < puzzleSize; i++){
            for(int j = 0; j < puzzleSize; j++){
                checkIfVisited.push_back(top.state[i][j]);
            }
        }
        // check if the state was already visited, if it was then skip
        if(hash.count(checkIfVisited)){
            continue;
        }

        // if it wasnt visited then add to hashmap
        hash.insert(checkIfVisited);
        
        if(canShiftUp(top)){ // check if you can shift up
            node new_node; // if you can then make a new node
            new_node = shiftUp(top); // set the node equal to the shifted up state
            new_node.cost = top.cost + 1; // change the cost + 1 because you are branching down again
            if(whichHeuristic == 2){ // see if a heuristic was called
                new_node.heuristicCost = MisplacedTileSearch(new_node);
            }
            else if(whichHeuristic == 3){
                new_node.heuristicCost = EuclideanDistanceSearch(new_node);
            }
            new_node.p = new node(top); // add the parent node which is the element selected from the priority queue
            pqueue.push(new_node); // push the element to the priority queue, it will use the compare struct made above to see where it should be placed
        }
        
        if(canShiftDown(top)){
            node new_node;
            new_node = shiftDown(top);
            new_node.cost = top.cost + 1;
            if(whichHeuristic == 2){
                new_node.heuristicCost = MisplacedTileSearch(new_node);
            }
            else if(whichHeuristic == 3){
                new_node.heuristicCost = EuclideanDistanceSearch(new_node);
            }
            new_node.p = new node(top);
            pqueue.push(new_node);
        }

        if(canShiftLeft(top)){
            node new_node;
            new_node = shiftLeft(top);
            new_node.cost = top.cost + 1;
            if(whichHeuristic == 2){
                new_node.heuristicCost = MisplacedTileSearch(new_node);
            }
            else if(whichHeuristic == 3){
                new_node.heuristicCost = EuclideanDistanceSearch(new_node);
            }
            new_node.p = new node(top);
            pqueue.push(new_node);
        }

        if(canShiftRight(top)){
            node new_node;
            new_node = shiftRight(top);
            new_node.cost = top.cost + 1;
            if(whichHeuristic == 2){
                new_node.heuristicCost = MisplacedTileSearch(new_node);
            }
            else if(whichHeuristic == 3){
                new_node.heuristicCost = EuclideanDistanceSearch(new_node);
            }
            new_node.p = new node(top);
            pqueue.push(new_node);
        }
    }
    cout << "Couldn't be Solved" << endl;
    return puzzle;
}