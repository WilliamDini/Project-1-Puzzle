#include <iostream>
#include <stack>

#include "headers/node.hpp"
#include "headers/problem.hpp"
using namespace std;

int main() {

  int userChoice = 0;

  cout << "Welcome to our 8-Puzzle Solver!" << endl << endl;

  Problem problem;

  while (true) {
    cout << "Type \"1\" to use a default puzzle or \"2\" to enter your own puzzle." << endl;
    cin >> userChoice;
    
    if (userChoice == 1) {
      break;
    }

    else if (userChoice == 2) {
      cout << "Enter your puzzle, use a zero to represent the blank." << endl;
      problem.userProblem();

      if (problem.GoalStateTest(problem.puzzle)) {
        cout << "Your puzzle is already solved." << endl;
        return 0;
      }

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
      node solved = problem.uniformCostSearch(1);

      bool notsolved = true;

      for(int i = 0; i < problem.getPuzzleSize(); i++){ // check each state to see if change was made
        for(int j = 0; j < problem.getPuzzleSize(); j++){
          if(solved.state[i][j] != problem.puzzle.state[i][j]){ 
            notsolved = false; // if there was that means its solved
          }
        }
      }
      if(notsolved) { // if notsolved is still true that means it wasnt solved
        break;
      }

      stack<node> path;
      path.push(solved);

      while(solved.p){
        path.push(*(solved.p));
        solved = *(solved.p);
      }
      while(!path.empty()){
        problem.printState(path.top());
        cout << endl;
        path.pop();
      }
      break;
    }

    else if (userChoice == 2) {
      node solved = problem.uniformCostSearch(2);

      bool notsolved = true;

      for(int i = 0; i < problem.getPuzzleSize(); i++){
        for(int j = 0; j < problem.getPuzzleSize(); j++){
          if(solved.state[i][j] != problem.puzzle.state[i][j]){
            notsolved = false;
          }
        }
      }
      if(notsolved) {
        break;
      }

      stack<node> path;
      path.push(solved);

      while(solved.p){
        path.push(*(solved.p));
        solved = *(solved.p);
      }
      while(!path.empty()){
        problem.printState(path.top());
        cout << endl;
        path.pop();
      }
      break;
    }

    else if (userChoice == 3) {
      node solved = problem.uniformCostSearch(3);
      int depth = solved.cost;

      bool notsolved = true;

      for(int i = 0; i < problem.getPuzzleSize(); i++){ 
        for(int j = 0; j < problem.getPuzzleSize(); j++){
          if(solved.state[i][j] != problem.puzzle.state[i][j]){
            notsolved = false; 
          }
        }
      }
      if(notsolved) { 
        break;
      }

      stack<node> path;
      path.push(solved);

      while(solved.p){
        path.push(*(solved.p));
        solved = *(solved.p);
      }
      while(!path.empty()){
        problem.printState(path.top());
        cout << endl;
        path.pop();
      }

      cout << depth << endl;
      cout << problem.getMaxExpanded() << endl;
      cout << problem.getMaxInQueue() << endl;
      
      break;
    }
  
    cin.clear();
    cin.ignore(80, '\n');
    cout << endl;
  }

  
  return 0;
}