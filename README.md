# 15 Puzzle Game

A classic sliding puzzle game implemented in C++. The 15 Puzzle (also known as Game of Fifteen or Gem Puzzle) consists of a 4x4 frame with 15 numbered square tiles and one empty space. The goal is to arrange the tiles in numerical order by sliding them into the empty space.

## Features

- 4x4 puzzle grid with 15 numbered tiles
- Simple keyboard controls (W, A, S, D)
- Random puzzle shuffling
- Move validation
- Puzzle solution checking
- Console-based user interface

## Implementation Details

The project is implemented using the following components:

- **FifteenPuzzle.h**: Class definition for the puzzle
- **FifteenPuzzle.cpp**: Implementation of the puzzle mechanics
- **15 puzzle game.cpp**: Main application file

### Core Functions

- Constructor: Initializes the puzzle board in a solved state
- `moveTile(char key)`: Handles tile movement based on keyboard input
- `shuffle(int moves)`: Randomly shuffles the puzzle board
- `display()`: Displays the current state of the puzzle board
- `isSolved()`: Checks if the puzzle is in the solved state

## How to Play

1. Run the game
2. Use W, A, S, D keys to move tiles:
   - **W**: Move a tile down into the empty space
   - **S**: Move a tile up into the empty space
   - **A**: Move a tile right into the empty space
   - **D**: Move a tile left into the empty space
3. Try to arrange the tiles in numerical order (1-15) with the empty space at the bottom right

## Requirements

- C++ compiler
- Standard library includes:
  - iostream
  - vector
  - random
  - ctime
  - iomanip

## Building the Project

Compile the source files using your preferred C++ compiler:

```bash
g++ -o 15puzzle "15 puzzle game.cpp" FifteenPuzzle.cpp -std=c++11
```

Then run the executable:

```bash
./15puzzle
```

## Sample Board Layout

```
+----+----+----+----+
|  1 |  2 |  3 |  4 |
+----+----+----+----+
|  5 |  6 |  7 |  8 |
+----+----+----+----+
|  9 | 10 | 11 | 12 |
+----+----+----+----+
| 13 | 14 | 15 |    |
+----+----+----+----+
```

This is the solved state of the puzzle.