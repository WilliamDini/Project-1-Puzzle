#include <iostream>
#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    // start state
    int tiles[9] = {1, 0, 3, 4, 2, 6, 7, 5, 8};
    for (int i = 0; i < puzzleSize; i++) {
        node tile;
        tile.state = tiles[i];
        tile.cost = 0;
        tile.heuristicCost = 0;
        // tile.p = ; // FIXME
        startState.push_back(tile);
    }

    // goal state
    int puzzleTiles = 1;

    for (int i = 0; i < puzzleSize - 1; i++) {
        node tile;
        tile.state = puzzleTiles;
        puzzleTiles += 1;
        goalState.push_back(tile);
    }

    node tile;
    tile.state = 0;
    goalState.push_back(tile);

}

void Problem::userProblem() {    // "constructor" based on user input
    int userInput = 0;
    
    for (auto i = startState.begin(); i != startState.end(); ++i) {
        cin >> userInput;
        i->state = userInput;
    }
}

// accessor functions —

int Problem::getPuzzleSize() {
    return puzzleSize - 1;
}

vector<node> Problem::getStartState() {
    return startState;
}
vector<node> Problem::getGoalState() {
    return goalState;
}

void Problem::printStartState() { // for testing purposes
    int counter = 0;

    for (auto i = startState.begin(); i != startState.end(); ++i) {
        
        if (i->state == 0) {
            cout << "* ";
        }

        else {
            cout << i->state << " ";
        }
        
        counter += 1;

        if (counter % 3 == 0) {
            cout << endl;
        }
    }

    cout << endl;
}

void Problem::printGoalState() { // for testing purposes
    int counter = 0;

    for (auto i = goalState.begin(); i != goalState.end(); ++i) {
        if (i->state == 0) {
            cout << "* ";
        }

        else {
            cout << i->state << " ";
        }

        counter += 1;

        if (counter % 3 == 0) {
            cout << endl;
        }
    }

    cout << endl;
}

bool Problem::GoalStateTest() {

    auto startIt = startState.begin();
    auto goalIt = goalState.begin();

    while ((startIt != startState.end()) || (goalIt != goalState.end())) {
        cout << "start: " << startIt->state << " goal: " << goalIt->state << endl;

        if (startIt->state != goalIt->state) {
            return false;
        }

        startIt++;
        goalIt++;
    }

    return true;
}

void Problem::MisplacedTileSearch(vector<node> x) {
    int goalS[this->puzzleSize];
    for(int i = 1; i != this->puzzleSize + 1; ++i) {
        goalS[i - 1] = i;
    }

    for(int j = 0; j < x.size(); j++) {
        if(goalS[j] != x.at(j).state) {

        }
    }
}

/*
    Goal State

    [1  2   3]
    [4  5   6]
    [7  8   *]

    1 =>    [1(0)  1(1)   1(2)]     2 =>    [2(1)  2(0)   2(1)]     2 =>    [3(2)  3(1)   3(0)]
            [1(1)  1(2)   1(3)]             [2(2)  2(1)   2(2)]             [3(3)  3(2)   3(1)]
            [1(2)  1(3)   1(4)]             [2(3)  2(2)   2(3)]             [3(4)  3(3)   3(2)]

    4 =>    [4(1)  4(2)   4(3)]     5 =>    [5(2)  5(1)   5(2)]     6 =>    [6(3)  6(2)   6(1)]
            [4(0)  4(1)   4(2)]             [5(1)  5(0)   5(1)]             [6(2)  6(1)   6(0)]
            [4(1)  4(2)   4(3)]             [5(2)  5(1)   5(2)]             [6(3)  6(2)   6(1)]

    7 =>    [7(2)  7(3)   7(4)]     8 =>    [8(3)  8(2)   8(3)]     * =>    [*(4)  *(3)   *(2)]
            [7(1)  7(2)   7(3)]             [8(2)  8(1)   8(2)]             [*(3)  *(2)   *(1)]
            [7(0)  7(1)   7(2)]             [8(1)  8(0)   8(1)]             [*(2)  *(1)   *(0)]

    Goal[SizeProblem] = [1, 2, 3,..., n]
*/