#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int sudokuSolver(int puzzle[][9]); // Function that solves the Sudoku/
int checkValidity(int number, int puzzle[][9], int row, int column); // Function that checks whether a number is valid in a cell.
int sudokuHelper(int puzzle[][9], int row, int column); // Recursive function that iterates through rows, columns and cell values to find unique solution.
void printSudoku(int puzzle[][9]); // Function to print the puzzle.

int main() 
{
    string filename = "Puzzle.txt"; // Name of the .txt file containing the puzzle. Missing cells are represented as zeros.
    int puzzle[9][9]; // Initializing a 9x9 array that will store the puzzle values. 
    string line;
    ifstream myfile (filename);
    if (myfile.is_open()) // Open .txt file.
    {
        int j = 0; // Keeps track of the row number.
        while (getline (myfile,line))
        {
            for (int i = 0; i < 9 ; i++) // Keeps track of the column number.
            {
                puzzle[j][i] = line[i]-'0'; // Store value in the array. '0' is subtracted to convert it from ASCII (string) to actual value.
            }
            j += 1;
        }
        myfile.close(); // Close the .txt file.
    }
    else
    {
        cout << "Unable to open file"; 
        system("pause");
        return 0; // End function since .txt file can not be opened.
    }
    cout << "\nThe original puzzle is shown below: \n \n";

    printSudoku(puzzle); // Print the given puzzle.

    if (sudokuSolver(puzzle)) // Solves sudoku. 1 if correctly solved and 0 if solution could not be found
    {
        cout << "\nThe sudoku puzzle has been sovled. The solution is shown below: \n \n";
        printSudoku(puzzle);
    } 
    else 
    {
        cout << "\nEither the algorithm could not find a valid solution or the given sudoku itself is invalid \n";
    }
    system("pause");
    return 0;
}

int sudokuSolver(int puzzle[][9]) 
{
    return sudokuHelper(puzzle, 0, 0); // Returns 1 if sudoku is solved, 0 if not. This is a recursive function, the puzzle parameter gets updated each time the function is called. 
}

int sudokuHelper(int puzzle[][9], int row, int column) 
{   
    
    if (row > 8) // Out of bounds indicating that all cells have been passed and therefore the sudoku has been solved. 
    {
        return 1;
    }

    
    if (puzzle[row][column]) // If the entry is non-zero, don't change it. 
    {
        if (column == 8) // Last column.
        {
            if (sudokuHelper(puzzle, row+1, 0)) // Check next row.
            {
                return 1;
            }
        } 
        else 
        {
            if (sudokuHelper(puzzle, row, column+1)) // Check next column.
            {
                return 1;
            }
        }
        return 0;
    }
    for (int nIteration = 1; nIteration<=9; nIteration++) // Potential value of the cell. 
    {
        if(checkValidity(nIteration, puzzle, row, column)) // Check if the potential value is valid in that cell. 
        {
            puzzle[row][column] = nIteration; // Assign potential value to that cell.
            if (column == 8) 
            {
                if (sudokuHelper(puzzle, row+1, 0)) 
                {
                    return 1;
                }
            } 
            else 
            {
                if (sudokuHelper(puzzle, row, column+1)) 
                {
                    return 1;
                }
            }
            puzzle[row][column] = 0; // If that potential value does not lead to a correct solution, then consider it "missing" again.
        }
    }
    return 0;
}

int checkValidity(int number, int puzzle[][9], int row, int column) {
    int i=0;

    for (i=0; i<9; i++) 
    {
        if (puzzle[i][column] == number) // Check column for potential value.
        {
            return 0;
        }        
        if (puzzle[row][i] == number) // Check row for potential value.
        {
            return 0;
        };
    }

    int k = 3*(row/3);
    int l = 3*(column/3);

    for(int x = k; x<k+3; x++) // Check respective square for potential value.
    {
        for(int y = l; y<l+3; y++)
        {
            if (puzzle[x][y] == number)
            {
                return 0;
            }            
        }
    }
    return 1;
}

void printSudoku(int puzzle[][9]) {
    int i=0, j=0;
    for (i=0; i<9; i++) 
    {
        for (j=0; j<9; j++) 
        {
            if (j == 2 || j == 5) 
            {
                cout << puzzle[i][j] << " | ";
            } 
            else if (j == 8) 
            {
                cout << puzzle[i][j] << "\n";
            } 
            else 
            {
                cout << puzzle[i][j] << " ";
            }
        }
        if (i == 2 || i == 5) 
        {
            cout << "------+-------+------\n";
        }
    }
}