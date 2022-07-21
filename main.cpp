#include <chrono>   // Timing
#include <iostream> // output stream
#include <unistd.h>

#define N 9

// Arbitray sudoku grid
int SudokuGrid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                        {5, 2, 0, 0, 0, 0, 0, 0, 0},
                        {0, 8, 7, 0, 0, 0, 0, 3, 1},
                        {0, 0, 3, 0, 1, 0, 0, 8, 0},
                        {9, 0, 0, 8, 6, 3, 0, 0, 5},
                        {0, 5, 0, 0, 9, 0, 6, 0, 0},
                        {1, 3, 0, 0, 0, 0, 2, 5, 0},
                        {0, 0, 0, 0, 0, 0, 0, 7, 4},
                        {0, 0, 5, 2, 0, 6, 3, 0, 0}};

// Simple sudoku grid
int SudokuGrid2[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 8, 0, 0, 0, 0, 4, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 6, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {2, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 2, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0}};

// Sudoku grid found to be difficult for recursive backtracking algoritms
int SudokuGrid3[N][N] = {{0, 6, 1, 0, 0, 7, 0, 0, 3},
                         {0, 9, 2, 0, 0, 3, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 8, 5, 3, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 5, 0, 4},
                         {5, 0, 0, 0, 0, 8, 0, 0, 0},
                         {0, 4, 0, 0, 0, 0, 0, 0, 1},
                         {0, 0, 0, 1, 6, 0, 8, 0, 0},
                         {6, 0, 0, 0, 0, 0, 0, 0, 0}};

/*
Function:
    Utilty function to print the Sudoku grid.

Parameters:
    grid: grid to be printed.

Return:
    void, Print function.
*/
void printGrid(int grid[N][N])
{
    // std::system("clear");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << grid[i][j] << " ";
            if (j == 2 || j == 5)
            {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if (i == 2 || i == 5)
        {
            std::cout << "---------------------" << std::endl;
        }
    }
    // usleep(1000);
}

/*
Function:
    A untility funtion to test the validity of a given
    number in a position, i.e. if it satisfies Sudoku

Parameters:
    grid : An NxN valid suduko grid which is being tested.
    row : Defaults to 0, defines the currently searched row.
    col : Deafults to 0, defines the currently searched col.
    num : Number being tested.

Return:
    Bool : returns true if a number is valid is a given
    positon, false otherwise.

*/
bool isValid(int grid[N][N], int row, int col, int num)
{
    // Check the row for validity
    for (int i = 0; i < N; i++)
    {
        if (grid[i][col] == num)
        {
            return false;
        }
    }

    // Check the column for validity
    for (int j = 0; j < N; j++)
    {
        if (grid[row][j] == num)
        {
            return false;
        }
    }

    // Check the box for validty
    // figure out which box the current box is in
    int currRow = row - (row % 3);
    int currCol = col - (col % 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[currRow + i][currCol + j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

/*
Function:
    Function which uses recursive backtracking to generate a solution
    for a given Sudoku grid.

Parameters:
    grid : An NxN valid suduko grid which is being tested.
    row : Defaults to 0, defines the currently searched row.
    col : Deafults to 0, defines the currently searched col.

Return :
    Bool: True if a solution for the given grid is found,
            False otherwise.
 */
bool Solve(int grid[N][N], int row = 0, int col = 0)
{
    // If complted print and return true
    if (row == N - 1 && col == N)
    {
        printGrid(grid);
        return true;
    }

    if (col == N)
    {
        row++;
        col = 0;
    }

    if (grid[row][col] > 0)
    {
        return Solve(grid, row, col + 1);
    }

    for (int num = 1; num < N + 1; num++)
    {
        if (isValid(grid, row, col, num))
        {
            grid[row][col] = num;
            // printGrid(grid);

            if (Solve(grid, row, col + 1))
            {
                return true;
            }
        }

        grid[row][col] = 0;
    }

    return false;
}

/*

Function:
    A function to excute and time the Solve() function using
    the chrono library.

Parameters:
    grid : An NxN valid suduko grid which is being tested

Return:
    Void, prints time taken to execute
*/
void timeSuduko(int grid[N][N])
{
    auto start = std::chrono::high_resolution_clock::now();
    if (!Solve(grid))
    {
        printf("No solution\n");
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl
              << std::endl;
}

int main()
{
    timeSuduko(SudokuGrid);
    timeSuduko(SudokuGrid2);
    timeSuduko(SudokuGrid3);
    return 0;
}