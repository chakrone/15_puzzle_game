#include "FifteenPuzzle.h"

#include <iostream>
using namespace std;
#include <vector>


FifteenPuzzle::FifteenPuzzle() {
	this->board = vector<vector<int>>(this->size, vector<int>(this->size));

	int value = 1;
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			board[i][j]==value++
		}
	}

}

