#ifndef FIFTEENPUZZLE_H_
#define FIFTEENPUZZLE_H_

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <string>

using namespace std;

enum class Difficulty {
    EASY = 30,
    MEDIUM = 100,
    HARD = 200
};

class FifteenPuzzle {
private:
    vector<vector<int>> board; // 2d board
    int EmptyRow; // empty tile row pos
    int EmptyCol; // empty tile col pos
    int size; // board size (customizable)
    int moveCount;
    stack<pair<int, int>> moveHistory; // Stores positions for undo

    // Helper methods for colored display
    void setConsoleColor(int colorCode) const;
    void resetConsoleColor() const;
    int getTileColor(int value) const;

public:
    // Constructor with customizable size (default is 4x4)
    FifteenPuzzle(int boardSize = 4);

    // Game mechanics
    void shuffle(int moves = 100);
    void shuffle(Difficulty level);
    bool moveTile(char key);
    bool isSolved() const;
    bool undoMove();
    char getHint() const;

    // Display methods
    void display() const;
    void displayEnhanced() const;
    string getBoardAsString() const; // For saving/loading

    // Getters
    int getMoveCount() const { return moveCount; }
    int getBoardSize() const { return size; }

    // Game state management
    void resetGame();
    void setBoardFromString(const string& boardStr);
};
#endif
