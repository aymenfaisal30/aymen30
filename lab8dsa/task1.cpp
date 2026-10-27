//Task 1: finding a peak element in a 2D array in O(n log n)
#include <iostream>
#include <climits>
using namespace std;


//this function is used for finding the row that has the largest value in a given column
//implementing this so that the element we pick is never smaller than its top and bottom neighbourss
int findMaxRowInColumn(int** grid, int rows, int col)
{
    int maxRow = 0;
    for (int i = 1; i < rows; i++)
    {
        if (grid[i][col] > grid[maxRow][col])
        {
            maxRow = i;
        }
    }
    return maxRow;
}

//this function is used for finding a peak element by doing binary search on the columns
//implementing it like this because cutting the columns in half each time gives us the log part of the complexity
bool findPeak(int** grid, int rows, int cols, int& peakRow, int& peakCol)
{
    int low = 0;
    int high = cols - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int maxRow = findMaxRowInColumn(grid, rows, mid);
        int current = grid[maxRow][mid];

        //if we are on the edge then there is no neighbour so i treat it as the smallest possible value
        int leftValue = (mid > 0) ? grid[maxRow][mid - 1] : INT_MIN;
        int rightValue = (mid < cols - 1) ? grid[maxRow][mid + 1] : INT_MIN;

        if (current >= leftValue && current >= rightValue)
        {
            peakRow = maxRow;
            peakCol = mid;
            return true;
        }
        else if (leftValue > current)
        {
            //bigger value on the left so the peak must be somewhere on the left half
            high = mid - 1;
        }
        else
        {
            //otherwise the right neighbour is bigger so we move to the right half
            low = mid + 1;
        }
    }

    //this should never actually happen because a peak always exists
    return false;
}

//this function is used for printing the 2D array so we can see the input clearly
void printGrid(int** grid, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
}

//this function is used for showing the neighbours of the peak we found
//implementing this so we can confirm by ourselves that the answer is actually a peak
void printNeighbours(int** grid, int rows, int cols, int r, int c)
{
    cout << "Neighbours: ";
    if (r > 0) cout << "Up=" << grid[r - 1][c] << " ";
    if (r < rows - 1) cout << "Down=" << grid[r + 1][c] << " ";
    if (c > 0) cout << "Left=" << grid[r][c - 1] << " ";
    if (c < cols - 1) cout << "Right=" << grid[r][c + 1] << " ";
    cout << endl;
}

//this function is used for freeing the memory of the dynamic 2D array
//implementing this so there is no memory leak after the program is done with the array
void deleteGrid(int** grid, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

int main()
{
    int rows, cols;
    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;

    //checking the input so the program does not crash on wrong sizes
    if (!cin || rows <= 0 || cols <= 0)
    {
        cout << "Rows and columns must be positive numbers." << endl;
        return 1;
    }

    //making the 2D array dynamically because the size is only known when the user enters it
    int** grid = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new int[cols];
    }

    cout << "Enter the elements row by row:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << "\nThe 2D array is:" << endl;
    printGrid(grid, rows, cols);

    int peakRow = -1;
    int peakCol = -1;

    if (findPeak(grid, rows, cols, peakRow, peakCol))
    {
        cout << "\nPeak element found: " << grid[peakRow][peakCol]
             << " at position (" << peakRow << ", " << peakCol << ")" << endl;
        printNeighbours(grid, rows, cols, peakRow, peakCol);
    }
    else
    {
        cout << "\nNo peak found." << endl;
    }

    deleteGrid(grid, rows);
    return 0;
}