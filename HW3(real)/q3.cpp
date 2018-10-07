#include <iostream>
using namespace std;

// This function recursively calculates and returns base^{exponent}
int pow(int base, int exponent)
{
    if (exponent == 0)                          // base case of 0 returns 1
        return 1;
    else
        return base * pow(base, exponent - 1);  // multiplies the base times the base to the power of the input minus 1
}

// This program calculates the value of a base to the power of an exponent for base and exponent > 0
int main()
{
    int base = 0;                                   // intialize and read in a base
    cin >> base;
    int exponent = 0;                               // intialize and read in an exponent
    cin >> exponent;

    if (base <= 0 || exponent <= 0)                 // return and print response if either the base or exponent are 0
        cout << "Both inputs must be positive\n";
    else
        cout << pow(base, exponent);                // calculate base to the power of exponent
}