#include <iostream>
#include "../headers/problem.hpp"

// initialize puzzle —

Problem::Problem() {    // default constructor
    
    // give start state
    int tiles[puzzleSize + 1] = {1, 0, 3, 4, 2, 6, 7, 5, 8};
    for (int i = 0; i < puzzleSize + 1; i++) {
        node tile;
        tile.state = tiles[i];
        // tile.cost = 0; // FIXME
        // tile.heuristicCost = 0; // FIXME
        // tile.p = ; // FIXME
        startState.push_back(tile);
    }

    // give goal state
    int puzzleTiles = 1;

    for (int i = 0; i < puzzleSize; i++) {
        node tile;
        tile.state = puzzleTiles;
        puzzleTiles += 1;
        goalState.push_back(tile);
    }

    node tile;
    tile.state = 0;
    goalState.push_back(tile);

}

Problem::Problem(vector<node> startState) {    // constructor based on user input

}

int Problem::getPuzzleSize() {
    return puzzleSize;
}

// void Problem::printStartState() { // for testing purposes
//     int counter = 0;

//     for (auto i = startState.begin(); i != startState.end(); ++i) {
        
//         if (i->state == 0) {
//             cout << "* ";
//         }

//         else {
//             cout << i->state << " ";
//         }
        
//         counter += 1;

//         if (counter % 3 == 0) {
//             cout << endl;
//         }
//     }

//     cout << endl;
// }

// void Problem::printGoalState() { // for testing purposes
//     int counter = 0;

//     for (auto i = goalState.begin(); i != goalState.end(); ++i) {
//         if (i->state == 0) {
//             cout << "* ";
//         }

//         else {
//             cout << i->state << " ";
//         }

//         counter += 1;

//         if (counter % 3 == 0) {
//             cout << endl;
//         }
//     }

//     cout << endl;
// }