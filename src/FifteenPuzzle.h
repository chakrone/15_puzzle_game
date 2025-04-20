#include <iostream>
using namespace std;
#include <vector>

#ifndef FIFTEENPUZZLE_H_
#define FIFTEENPUZZLE_H_

class FifteenPuzzle {
private:
	vector<vector<int>> board; // 2d board
	int EmptyRow; // empty tile row pos
	int EmptyCol; // empty tile col pos
	const int size=4; // board size

public:
	FifteenPuzzle();
	void shuffle(int moves = 100);
	void display() const;
	bool moveTile(char key);
	bool isSolved() const;

};

#endif /* FIFTEENPUZZLE_H_ */
