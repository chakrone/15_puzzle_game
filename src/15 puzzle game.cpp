#include <iostream>
#include <vector>
#include <string>
#include "FifteenPuzzle.h"

using namespace std;

int main() {
	FifteenPuzzle game;

	char input;
	int counter = 0;
	cout << "Welcome to the 15 puzzle game" << endl;
	cout << "to play press w,s,a or d to move the empty space up, down, left or right respectively." << endl;
	cout << "To quit the game press q" << endl;

	game.shuffle();
	game.display();

	while (true) {
		if (game.isSolved()) {
			cout << "You Won in " << counter <<  " moves !!" << endl;
			break;
		}

		cout << "moves: " << counter << endl;
		cout << "Enter your move (w/a/s/d) or 'q' to quit : ";
		cin >> input;
		if (input =='q' || input == 'Q') {
			cout << "thanks for playing" << endl;
			break;
		}

		if (game.moveTile(input)) {
					counter++;
				} else {
					cout << "Invalid move! Try again." << endl;
				}

		cout << "board state : " << endl;
		game.display();
	}

	return 0;
}
