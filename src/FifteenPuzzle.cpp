#include "FifteenPuzzle.h"
using namespace std;

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif



FifteenPuzzle::FifteenPuzzle(int boardSize) : size(boardSize), moveCount(0) {
    // Validate board size (minimum 2x2, maximum 8x8)
    if (size < 2) size = 2;
    if (size > 8) size = 8;

    // Initialize the board
    this->board = vector<vector<int>>(this->size, vector<int>(this->size));

    // Fill the board in the solved state
    int value = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this->board[i][j] = value++;
        }
    }

    // Set the last position to 0 (empty)
    this->board[this->size-1][this->size-1] = 0;
    this->EmptyCol = size-1;
    this->EmptyRow = size-1;

    // Clear move history
    while (!moveHistory.empty()) moveHistory.pop();
}

// Dynamic board display method
void FifteenPuzzle::display() const {
    // Create the top border with the right width
    for (int j = 0; j < size; j++) {
        cout << "+----";
    }
    cout << "+\n";

    // Display each row
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "| ";
            if (this->board[i][j] == 0) {
                cout << "   ";
            } else {
                // Adjust width based on the number of digits
                if (this->board[i][j] < 10) {
                    cout << " " << this->board[i][j] << " ";
                } else {
                    cout << this->board[i][j] << " ";
                }
            }
        }
        cout << "|\n";

        // Row separator
        for (int j = 0; j < size; j++) {
            cout << "+----";
        }
        cout << "+\n";
    }
}

// Enhanced display with similar dynamic sizing
void FifteenPuzzle::displayEnhanced() const {
    // Create the top border with the right width
    for (int j = 0; j < size; j++) {
        cout << "+----";
    }
    cout << "+\n";

    // Display each row with colors
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "| ";
            if (this->board[i][j] == 0) {
                setConsoleColor(36); // Cyan for empty space
                cout << "   ";
            } else {
                int color = getTileColor(this->board[i][j]);
                setConsoleColor(color);

                // Adjust width based on the number of digits
                if (this->board[i][j] < 10) {
                    cout << " " << this->board[i][j] << " ";
                } else {
                    cout << this->board[i][j] << " ";
                }
            }
            resetConsoleColor();
        }
        cout << "|\n";

        // Row separator
        for (int j = 0; j < size; j++) {
            cout << "+----";
        }
        cout << "+\n";
    }
}

// Get color for a tile based on whether it's in the correct position
int FifteenPuzzle::getTileColor(int value) const {
    if (value == 0) return 36; // Cyan for empty

    // Calculate expected position
    int targetRow = (value - 1) / size;
    int targetCol = (value - 1) % size;

    // Find actual position
    int actualRow = -1, actualCol = -1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == value) {
                actualRow = i;
                actualCol = j;
                break;
            }
        }
        if (actualRow != -1) break;
    }

    // Green if in correct position, white otherwise
    if (targetRow == actualRow && targetCol == actualCol) {
        return 32; // Green
    }
    return 37; // White
}

// Save/load board state methods
string FifteenPuzzle::getBoardAsString() const {
    string result = to_string(size) + "|";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result += to_string(board[i][j]);
            if (i != size-1 || j != size-1) {
                result += ",";
            }
        }
    }

    return result;
}

void FifteenPuzzle::setBoardFromString(const string& boardStr) {
    // Parse the board size
    size_t delimPos = boardStr.find('|');
    if (delimPos == string::npos) return;

    int newSize = stoi(boardStr.substr(0, delimPos));
    if (newSize < 2 || newSize > 8) return;

    // Resize the board
    size = newSize;
    board = vector<vector<int>>(size, vector<int>(size));

    // Parse the board values
    string values = boardStr.substr(delimPos + 1);
    int pos = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            size_t commaPos = values.find(',', pos);
            string valueStr;

            if (commaPos == string::npos) {
                valueStr = values.substr(pos);
            } else {
                valueStr = values.substr(pos, commaPos - pos);
                pos = commaPos + 1;
            }

            int value = stoi(valueStr);
            board[i][j] = value;

            // Track empty position
            if (value == 0) {
                EmptyRow = i;
                EmptyCol = j;
            }
        }
    }

    // Clear move history
    while (!moveHistory.empty()) moveHistory.pop();
    moveCount = 0;
}
