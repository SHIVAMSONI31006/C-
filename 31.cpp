#include <iostream>
#include <vector>

const int N = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number is valid in a given cell
bool isValid(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < N; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// The main Sudoku solving function using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;

    // Find the first empty cell (0)
    bool foundEmpty = false;
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) {
            break;
        }
    }

    // If no empty cell is found, the puzzle is solved
    if (!foundEmpty) {
        return true;
    }

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            // Place the valid number
            grid[row][col] = num;

            // Recurse to solve the rest of the puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If the recursive call failed, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number worked, return false
    return false;
}

int main() {
    std::vector<std::vector<int>> puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Unsolved Sudoku Puzzle:" << std::endl;
    printGrid(puzzle);
    std::cout << "\nSolving...\n" << std::endl;

    if (solveSudoku(puzzle)) {
        std::cout << "Solved Sudoku Puzzle:" << std::endl;
        printGrid(puzzle);
    } else {
        std::cout << "No solution exists for the given puzzle." << std::endl;
    }

    return 0;
}