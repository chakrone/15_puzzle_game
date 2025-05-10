#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <conio.h> // For _getch() to capture keypress without Enter
#include "FifteenPuzzle.h"

using namespace std;

// Function to display the game menu
void displayMenu() {
    cout << "\n=== 15 PUZZLE GAME ===\n";
    cout << "1. New Game (Easy)\n";
    cout << "2. New Game (Medium)\n";
    cout << "3. New Game (Hard)\n";
    cout << "4. View High Scores\n";
    cout << "5. How to Play\n";
    cout << "6. Quit\n";
    cout << "Select an option: ";
}

// Function to display the in-game help
void displayHelp() {
    cout << "\n=== HOW TO PLAY ===\n";
    cout << "The goal is to arrange the tiles in numerical order from 1-15, with the empty space in the bottom right.\n\n";
    cout << "Controls:\n";
    cout << "  W or Up Arrow    - Move empty space up\n";
    cout << "  S or Down Arrow  - Move empty space down\n";
    cout << "  A or Left Arrow  - Move empty space left\n";
    cout << "  D or Right Arrow - Move empty space right\n";
    cout << "  U               - Undo last move\n";
    cout << "  H               - Get a hint\n";
    cout << "  M               - Return to main menu\n";
    cout << "  Q               - Quit current game\n\n";
    cout << "Press any key to continue...";
    _getch();
    system("cls"); // Clear screen (Windows specific, use "clear" for Unix/Linux)
}

int main() {
    FifteenPuzzle game;
    bool gameRunning = false;
    bool applicationRunning = true;
    int moveCounter = 0;
    auto startTime = chrono::steady_clock::now();

    srand(static_cast<unsigned int>(time(nullptr)));

    while (applicationRunning) {
        if (!gameRunning) {
            system("cls"); // Clear screen
            displayMenu();

            int choice;
            cin >> choice;

            switch (choice) {
                case 1: // Easy
                    game = FifteenPuzzle();
                    game.shuffle(Difficulty::EASY);
                    gameRunning = true;
                    moveCounter = 0;
                    startTime = chrono::steady_clock::now();
                    break;

                case 2: // Medium
                    game = FifteenPuzzle();
                    game.shuffle(Difficulty::MEDIUM);
                    gameRunning = true;
                    moveCounter = 0;
                    startTime = chrono::steady_clock::now();
                    break;

                case 3: // Hard
                    game = FifteenPuzzle();
                    game.shuffle(Difficulty::HARD);
                    gameRunning = true;
                    moveCounter = 0;
                    startTime = chrono::steady_clock::now();
                    break;

                case 4: // View High Scores
                    cout << "\n=== HIGH SCORES ===\n";
                    // TODO: Implement high score loading and display
                    cout << "No high scores available yet.\n";
                    cout << "Press any key to continue...";
                    _getch();
                    break;

                case 5: // How to Play
                    displayHelp();
                    break;

                case 6: // Quit
                    cout << "Thanks for playing!\n";
                    applicationRunning = false;
                    break;

                default:
                    cout << "Invalid option. Press any key to continue...";
                    _getch();
                    break;
            }
        }
        else {
            // Game is running
            system("cls"); // Clear screen

            // Calculate and display time elapsed
            auto currentTime = chrono::steady_clock::now();
            chrono::duration<double> elapsed = currentTime - startTime;

            cout << "=== 15 PUZZLE GAME ===\n";
            cout << "Moves: " << moveCounter << " | ";
            cout << "Time: " << fixed << setprecision(1) << elapsed.count() << " seconds\n";
            cout << "U: Undo | H: Hint | M: Menu | Q: Quit\n\n";

            // Display the board with colors
            game.displayEnhanced();

            // Check if solved
            if (game.isSolved()) {
                cout << "\nCONGRATULATIONS! You solved the puzzle!\n";
                cout << "Total moves: " << moveCounter << "\n";
                cout << "Time taken: " << fixed << setprecision(2) << elapsed.count() << " seconds\n";

                // TODO: Check if this is a high score and save it

                cout << "Press any key to return to the menu...";
                _getch();
                gameRunning = false;
                continue;
            }

            // Get user input without requiring Enter
            cout << "Enter your move: ";
            char input = _getch();

            // Process movement keys
            bool moved = false;
            switch (input) {
                case 'w': case 'W': case 72: // Up arrow
                    moved = game.moveTile('w');
                    break;

                case 's': case 'S': case 80: // Down arrow
                    moved = game.moveTile('s');
                    break;

                case 'a': case 'A': case 75: // Left arrow
                    moved = game.moveTile('a');
                    break;

                case 'd': case 'D': case 77: // Right arrow
                    moved = game.moveTile('d');
                    break;

                case 'u': case 'U': // Undo
                    if (game.undoMove()) {
                        moveCounter--;
                    } else {
                        cout << "\nNo moves to undo!";
                        this_thread::sleep_for(chrono::milliseconds(800));
                    }
                    break;

                case 'h': case 'H': // Hint
                    {
                        char hint = game.getHint();
                        cout << "\nHint: Try moving " <<
                            (hint == 'w' ? "UP" :
                             hint == 's' ? "DOWN" :
                             hint == 'a' ? "LEFT" : "RIGHT");
                        this_thread::sleep_for(chrono::milliseconds(1500));
                    }
                    break;

                case 'm': case 'M': // Return to menu
                    gameRunning = false;
                    break;

                case 'q': case 'Q': // Quit game
                    cout << "\nQuitting current game...";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    gameRunning = false;
                    break;

                default:
                    cout << "\nInvalid input!";
                    this_thread::sleep_for(chrono::milliseconds(800));
                    break;
            }

            if (moved) {
                moveCounter++;
            }
        }
    }

    return 0;
}
