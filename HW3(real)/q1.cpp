#include <iostream>
using namespace std;

// print_int prints takes an int and prints it
void print_int(int integer)
    {
        cout << integer;    // outputs the argument
    }

// read_int is a helper function that reads and returns an int
int read_int()
    {
        int input = 0;      // declares an int variable called input 
        cin >> input;       // reads in an int and input to equal it
        return input;       // returns the input
    }

// print_smallest does the actual comparing of three integers that ahev been inputed
int return_smallest_3()       
    {
        int x = read_int(); // assign the variable x to an inputed int
        int y = read_int(); // assign the variable y to an inputed int
        int z = read_int(); // assign the variable z to an inputed int

        int smallest = 0;   // create a variable that will hold the smallest value
        if (x > y)          // if x is bigger that y, y becomes small; otherwise x becomes smallest
            smallest = y;
        else 
            smallest = x;
        if (smallest > z)   // if z is smaller that the smallest of x and y, z becomes smallest
            smallest = z;
        return smallest;
    }

// Main function prints the smallest of three inputed variables
int main()
    {
        print_int(return_smallest_3());    // calls the print_smallest function
    }