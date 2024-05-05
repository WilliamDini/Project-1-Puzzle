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
    int tiles[9] = {1,2,3,4,8,0,7,6,5}; // to be populated in the dynamic vector
    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            puzzle.state[i][j] = tiles[counter];    // build the start state puzzle, one integer at a time
            counter++;
        }
    }
}

void Problem::userProblem() {    // "constructor" based on user input
    int userInput = 0;
    
    for (int i = 0; i < 3; ++i) {   // puzzle column
        for(int j = 0; j < 3; ++j) {    // puzzle row
            cin >> userInput;
            puzzle.state[i][j] = userInput; // change the start state puzzle according to user input
        }
    }
}

int Problem::getPuzzleSize() {
    return puzzleSize;
}

void Problem::printStartState() {   // print for start state puzzle
    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            cout << puzzle.state[i][j] << " ";
        }
        cout << endl;
    }
}

void Problem::printState(node puzzleInput) { // print for current state puzzle
    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            cout << puzzleInput.state[i][j] << " ";
        }
        cout << endl;
    }
}

bool Problem::GoalStateTest(node puzzleInput) {
    int counter = 1;

    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {    // puzzle row
            if(puzzleInput.state[i][j]==counter) {  // checking if the numbers in the puzzle are in increasing order
                counter++;
                continue;
            }
            else{
                if(counter == 9 && puzzleInput.state[i][j]==0) { // checking if the ninth number is a 0
                    continue;
                }
                return false;
            }
        }
    }
    
    return true;
}

int Problem::getMaxExpanded(){
    return numExpanded;
}

int Problem::getMaxInQueue(){
    return maxInQueue;
}

bool Problem::canShiftUp(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            if(inputPuzzle.state[i][j]==0) {    // if the location of the 0 is found, store it
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(ilocation==0) {  // if 0 is in the top row, shift up is impossible
        return false;
    }
    return true;
}

bool Problem::canShiftDown(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            if(inputPuzzle.state[i][j]==0) {    // if the location of the 0 is found, store it
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(ilocation==2) {  // if 0 is in the bottom row, shift down is impossible
        return false;
    }
    return true;
}

bool Problem::canShiftLeft(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            if(inputPuzzle.state[i][j]==0) {    // if the location of the 0 is found, store it
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(jlocation==0) { // if 0 is in the leftmost column, shift left is impossible
        return false;
    }
    return true;
}

bool Problem::canShiftRight(node inputPuzzle) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {   // puzzle column
        for(int j = 0; j < puzzleSize; ++j) {   // puzzle row
            if(inputPuzzle.state[i][j]==0) {    // if the location of the 0 is found, store it
                ilocation = i;
                jlocation = j;
            }
        }
    }
    if(jlocation==2) {  // if 0 is in the rightmost column, shift right is impossible
        return false;
    }
    return true;
}

node Problem::shiftLeft(node puzzleInput) {
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            if(puzzleInput.state[i][j]==0){ // store the location of the 0
                ilocation = i;
                jlocation = j;
            }
        }
    }
    
    // shift the position of the 0 to the left by switching it with its left neighbor
    int holder = puzzleInput.state[ilocation][jlocation-1];
    puzzleInput.state[ilocation][jlocation-1] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}

node Problem::shiftRight(node puzzleInput){
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            if(puzzleInput.state[i][j]==0) {    // store the location of the 0
                ilocation = i;
                jlocation = j;
            }
        }
    }
    
    // shift the position of the 0 to the right by switching it with its right neighbor 
    int holder = puzzleInput.state[ilocation][jlocation+1];
    puzzleInput.state[ilocation][jlocation+1] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}

node Problem::shiftUp(node puzzleInput){
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            if(puzzleInput.state[i][j]==0) {    // store the location of the 0
                ilocation = i;
                jlocation = j;
            }
        }
    }

    // shift the position of the 0 upwards by switching it with its upstairs neighbor
    int holder = puzzleInput.state[ilocation-1][jlocation];
    puzzleInput.state[ilocation-1][jlocation] = 0;
    puzzleInput.state[ilocation][jlocation] = holder;

    return puzzleInput;
}

node Problem::shiftDown(node puzzleInput){
    int ilocation = 0;
    int jlocation = 0;

    for(int i = 0; i < puzzleSize; ++i) {
        for(int j = 0; j < puzzleSize; ++j) {
            if(puzzleInput.state[i][j]==0) {    // store the location of the 0
                ilocation = i;
                jlocation = j;
            }
        }
    }

    // shift the position of the 0 downwards by switching it with its downstairs neighbor
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
            if(inputPuzzle.state[i][j] != goalS[i][j]) {    // increase heuristic count if the number doesn't match the one in the goal
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
                heuristicCost += sqrt(pow(i-igoallocation, 2) + pow(j-igoallocation, 2));   // distance formula
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
        if(pqueue.size() > maxInQueue){
            maxInQueue = pqueue.size();
        }

        node top = pqueue.top();
        pqueue.pop();

        if(GoalStateTest(top)){
            return top;
        }
        numExpanded++;

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