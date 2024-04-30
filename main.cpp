#include <iostream>
#include "problem.hpp"

#include "node.h"

using namespace std;

int main() {

  int userChoice = 0;

  cout << "Welcome to [TEAM NAME] 8-Puzzle Solver!" << endl << endl;

  // create an instance of Problem class, with the default puzzle

  while (true) {
    cout << "Type \"1\" to use a default puzzle or \"2\" to enter your own puzzle." << endl;
    cin >> userChoice;

    if (userChoice == 1) {
      break;
    }
    
    else if (userChoice == 2) {
      cout << "Enter your puzzle, use a zero to represent the blank." << endl;
      // call the problem function that populates the puzzle array according to the user's desires
      break;
    }
  
    cin.clear();
    cin.ignore(80, '\n');
    cout << endl;
  }

  cout << "A puzzle has been created." << endl << endl;

  userChoice = 0;   // reset the variable for next choice

  while (true) {
    cout << "Enter your choice of algorithm. Only type the number of the chosen option." << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << "3. A* with the Euclidean Distance heuristic" << endl;
  
    cin >> userChoice;

    if (userChoice == 1) {
      // call uniform cost search
      break;
    }

    else if (userChoice == 2) {
      // call misplaced tile heuristic
      break;
    }

    else if (userChoice == 3) {
      // call euclidean distance heuristic
      break;
    }
  
    cin.clear();
    cin.ignore(80, '\n');
    cout << endl;
  }
  

  return 0;
}
