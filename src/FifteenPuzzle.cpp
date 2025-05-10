#include "FifteenPuzzle.h"
using namespace std;

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>


FifteenPuzzle::FifteenPuzzle() { // @suppress("Class members should be properly initialized")
	this->board = vector<vector<int>>(this->size, vector<int>(this->size));

	int value = 1;
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			this->board[i][j] = value++;
		}
	}

	this->board[this->size-1][this->size-1] = 0;
	this->EmptyCol = size-1;
	this->EmptyRow = size-1;

}

bool FifteenPuzzle::moveTile(char key){
	int newRow = this->EmptyRow;
	int newCol = this->EmptyCol;

	switch(key) {
	case 'W': case 'w' : newRow--; break;
	case 'S': case 's' : newRow++; break;
	case 'A': case 'a' : newCol--; break;
	case 'D': case 'd' : newCol++; break;
	default : return false;
	}

	// check if move is valid
	if (newRow<0 || newRow>this->size-1 || newCol<0 || newCol>this->size-1) {
		return false;
	}

	this->board[this->EmptyRow][this->EmptyCol] = this->board[newRow][newCol];
	this->board[newRow][newCol] = 0;
	this->EmptyRow = newRow;
	this->EmptyCol = newCol;

	return true;
}


void FifteenPuzzle::shuffle(int moves) {
	// mersenne twister random number generator algorithm seeded with time
	mt19937 rng(static_cast<unsigned int>(time(nullptr)));

	for (int i=0; i<moves; ++i) {
		// check for the possible moves and inserting them into a vector for later use
		vector<char> possibleMoves;
		if (this->EmptyRow > 0) possibleMoves.push_back('w');
		if (this->EmptyRow < this->size -1) possibleMoves.push_back('s');
		if (this->EmptyCol > 0) possibleMoves.push_back('a');
		if (this->EmptyCol < this->size -1) possibleMoves.push_back('d');

		// Create a uniform distribution for integers from 0 to size-1
		uniform_int_distribution<size_t> dist(0, possibleMoves.size()-1);
		char direction = possibleMoves[dist(rng)];

		moveTile(direction);
	}
}

void FifteenPuzzle::display() const {
	for (int i=0; i<size; i++) {
		cout << "+----+----+----+----+\n";
		for (int j=0; j<size; j++) {
			cout << "| " ;
			if (this->board[i][j] == 0)	cout << "   ";
			else cout << setw(2) <<  this->board[i][j] << " ";
		}
		cout << "|\n";
	}
	cout << "+----+----+----+----+\n";
}

bool FifteenPuzzle::isSolved() const {
	int value = 1 ;
	for (int i=0; i<this->size; ++i) {
		for (int j=0; j<this->size; ++j) {
			if (i == this->size-1 && j == this->size-1) {
				return this->board[i][j] == 0;
			}

			else if (this->board[i][j] != value++) {
				return false;
			}
		}
	}
	return true;
}
