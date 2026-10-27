//Task 2: 
//knight's tour using backtracking with an optimization
#include <iostream>
using namespace std;

const int MAX_N = 50;

//this array is used for storing the board, each cell keeps the move number or -1 if not visited
int board[MAX_N][MAX_N];

//these two arrays store the 8 possible L shaped moves of the knight
const int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

//this function is used for checking if a square is inside the board and not visited yet
bool isSafe(int x, int y, int n)
{
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

//this function is used for counting how many unvisited squares the knight can jump to from (x, y)
//implementing this for warnsdorff's rule because we want to go to the square with the least options first
int countOnwardMoves(int x, int y, int n)
{
    int count = 0;
    for (int k = 0; k < 8; k++)
    {
        if (isSafe(x + moveX[k], y + moveY[k], n))
        {
            count++;
        }
    }
    return count;
}

//this function is used for sorting the possible moves by their degree using insertion sort
//implementing it so the move index array moves together with the degree array and they stay matched
//there are at most 8 moves so this takes constant time and does not change the overall complexity
void sortMovesByDegree(int degree[], int moveIndex[], int count)
{
    for (int i = 1; i < count; i++)
    {
        int keyDegree = degree[i];
        int keyIndex = moveIndex[i];
        int j = i - 1;

        while (j >= 0 && degree[j] > keyDegree)
        {
            degree[j + 1] = degree[j];
            moveIndex[j + 1] = moveIndex[j];
            j--;
        }

        degree[j + 1] = keyDegree;
        moveIndex[j + 1] = keyIndex;
    }
}

//this function is used for solving the tour recursively using backtracking
//implementing the move ordering here so the knight tries the most promising moves first
bool solveTour(int x, int y, int moveNumber, int n)
{
    //if we have placed all the moves then every square is visited and the tour is complete
    if (moveNumber == n * n)
    {
        return true;
    }

    //storing each valid next move along with how many onward moves it has
    int degree[8];
    int moveIndex[8];
    int count = 0;

    for (int k = 0; k < 8; k++)
    {
        int nextX = x + moveX[k];
        int nextY = y + moveY[k];
        if (isSafe(nextX, nextY, n))
        {
            degree[count] = countOnwardMoves(nextX, nextY, n);
            moveIndex[count] = k;
            count++;
        }
    }

    //sorting so the move with the fewest onward options comes first
    sortMovesByDegree(degree, moveIndex, count);

    for (int i = 0; i < count; i++)
    {
        int nextX = x + moveX[moveIndex[i]];
        int nextY = y + moveY[moveIndex[i]];

        board[nextX][nextY] = moveNumber;

        if (solveTour(nextX, nextY, moveNumber + 1, n))
        {
            return true;
        }

        //this move did not work so we undo it and try the next one, this is the backtracking part
        board[nextX][nextY] = -1;
    }

    return false;
}

//this function is used for printing a number in a fixed width of 4 characters
//implementing this so the columns of the board line up properly without using any library
void printPadded(int value)
{
    int digits = 1;
    int temp = value;
    while (temp >= 10)
    {
        temp /= 10;
        digits++;
    }
    for (int i = digits; i < 4; i++)
    { cout << " "; }
    cout << value;
}

//this function is used for printing the board where each number shows the order the knight visited that square
void printBoard(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {  printPadded(board[i][j]); }
        cout << endl;
    }
}

int main()
{
    int n, startX, startY;
    cout << "Enter the size of the board (N): ";
    cin >> n;

    //keeping a limit so the recursion and the printed board stay reasonable
    if (!cin || n <= 0 || n > MAX_N)
    {
        cout << "Please enter N between 1 and " << MAX_N << "." << endl;
        return 1;
    }

    cout << "Enter starting position x and y (0 based): ";
    cin >> startX >> startY;

    if (!cin || startX < 0 || startX >= n || startY < 0 || startY >= n)
    {
        cout << "Starting position is outside the board." << endl;
        return 1;
    }

    //-1 means the square is not visited yet
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = -1;
        }
    }
    board[startX][startY] = 0;

    if (solveTour(startX, startY, 1, n))
    {
        cout << "\nKnight's tour found:" << endl;
        printBoard(n);
    }
    else
    {
        cout << "\nNo knight's tour exists from (" << startX << ", " << startY
             << ") on a " << n << "x" << n << " board." << endl;
    }

    return 0;
}