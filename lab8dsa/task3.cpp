//Task 3: 
//iterative solution of tower of hanoi
#include <iostream>
using namespace std;

//instead of recursion i used three stacks,one for each peg and i wrote the stack myself
//the pattern i used is that the moves repeat in a cycle of 3:
//move 1: legal move between source n destination
//move 2: legal move between source n auxiliary
//move 3: legal move between auxiliary n destinationn


const int MAX_DISKS = 20;

//this struct is used for making my own stack of disks using a simple array
//implementing push, pop, peek and isEmpty because these are the only operations the pegs need
struct DiskStack
{
    int items[MAX_DISKS];
    int top = -1;

    //this function is used for checking if there are no disks on the stack
    bool isEmpty()
    {
        return top == -1;
    }

    //this function is used for putting a disk on top of the stack
    void push(int disk)
    {
        if (top < MAX_DISKS - 1)
        {
            items[++top] = disk;
        }
    }

    //this function is used for removing the top disk and giving it back
    int pop()
    {
        return items[top--];
    }

    //this function is used for looking at the top disk without removing it
    int peek()
    {
        return items[top];
    }
};

//this struct is used for representing one peg with its name and the disks on it
struct Peg
{
    char name;
    DiskStack disks;
};

//this function is used for moving the top disk from one peg to another and printing the move
void moveDisk(Peg& from, Peg& to)
{
    int disk = from.disks.pop();
    to.disks.push(disk);
    cout << "Move disk " << disk << " from " << from.name << " to " << to.name << endl;
}

//this function is used for making the one legal move possible between two pegs
//implementing it so the smaller disk always goes on top and we never break the rules
void moveBetween(Peg& first, Peg& second)
{
    if (first.disks.isEmpty())
    {
        //first peg is empty so the disk has to move from second to first
        moveDisk(second, first);
    }
    else if (second.disks.isEmpty())
    {
        moveDisk(first, second);
    }
    else if (first.disks.peek() < second.disks.peek())
    {
        //top of first is smaller so it is allowed to go on top of second
        moveDisk(first, second);
    }
    else
    {
        moveDisk(second, first);
    }
}

//this function is used for solving the whole puzzle iteratively and printing every move
//implementing the cycle of 3 moves here and swapping pegs when n is even
void towerOfHanoi(int n)
{
    Peg source;
    Peg auxiliary;
    Peg destination;
    source.name = 'A';
    auxiliary.name = 'B';
    destination.name = 'C';

    //putting the disks on the source peg with the biggest at the bottom
    for (int disk = n; disk >= 1; disk--)
    {
        source.disks.push(disk);
    }

    //using pointers so i can swap the roles of the pegs without copying the stacks
    Peg* src = &source;
    Peg* aux = &auxiliary;
    Peg* dest = &destination;

    if (n % 2 == 0)
    {
        //swapping by hand with a temporary pointer
        Peg* temp = aux;
        aux = dest;
        dest = temp;
    }

    //2^n - 1 moves in total, shifting 1 left by n is the same as 2^n
    unsigned long long totalMoves = (1ULL << n) - 1;

    for (unsigned long long i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 1)
        {
            moveBetween(*src, *dest);
        }
        else if (i % 3 == 2)
        {
            moveBetween(*src, *aux);
        }
        else
        {
            moveBetween(*aux, *dest);
        }
    }

    cout << "\nTotal moves: " << totalMoves << endl;
}

int main()
{
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;

    //limiting the disks because the moves grow as 2^N and printing them takes forever after this
    if (!cin || n <= 0 || n > MAX_DISKS)
    {
        cout << "Please enter a number of disks between 1 and " << MAX_DISKS << "." << endl;
        return 1;
    }

    cout << "\nMoves to transfer " << n << " disks from peg A to peg C:" << endl;
    towerOfHanoi(n);
    return 0;
}