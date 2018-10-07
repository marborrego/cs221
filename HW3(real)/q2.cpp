#include <iostream>
using namespace std;

// This function takes two ints as inputs and returns True iff the latter is a multiple of the former
bool isMultiple(int mult, int base)
{
    if (mult % base == 0)           // if there is no remainder from mult//base return true
        return true;
    else                            // anything else returns false
        return false;
}

// This program reads in an int and then 10 more ints and prints out how many of those 10 were multiples of the original
int main()
{
    int num = 0;                            // num is the variable that we will compare the other 10 inputs to
    cin >> num;
    int number_mult = 0;                    // this variable will act as a counter of how many multiples there are
    int check_number = 0;                   // this variable will hold the value of the input for each loop
    int n = 10;                             // a count for the 10 int inputs

    while (n > 0) {                         // a while loop that cycles 10 times
        cin >> check_number;
        if (isMultiple(check_number, num))  // if the number is a multiple of the original input, add to the count
            ++number_mult;
        -- n;                               // increment the loop count
    }

    cout << number_mult;                    // print the number of multiples
}