#include "FifteenPuzzle.h"

#include <iostream>
using namespace std;
#include <vector>


FifteenPuzzle::FifteenPuzzle() { // @suppress("Class members should be properly initialized")
	this->board = vector<vector<int>>(this->size, vector<int>(this->size));

	int value = 1;
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			board[i][j]==value++;
		}
	}

	board[this->size-1][this->size] == 0;
	this->EmptyCol = size-1;
	this->EmptyRow = size-1;

}

bool FifteenPuzzle::moveTile(char key){
	int newRow = this->EmptyRow;
	int newCol = this->EmptyCol;

	switch(char direction) {
	case 'W': case 'w' : newRow--; break;
	case 'S': case 's' : newRow++; break;
	case 'A': case 'a' : newCol--; break;
	case 'D': case 'd' : newCol++; break;
	default : return false;
	}

	// check if move is valid
	if (newRow<0 || newRow>this->size-1 || newCol<0 || newCol>this->size) {
		return false;
	}

	this->board[this->EmptyRow][this->EmptyCol] = this->board[newRow][newCol];
	this->board[newRow][newCol] = 0;
	this->EmptyRow = newRow;
	this->EmptyCol = newCol;

	return true;
}

