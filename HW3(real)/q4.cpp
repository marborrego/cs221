#include <iostream>
using namespace std;

// This function takes two ints as input and calculates log former base latterint log(int num, int base)
int log(int num, int base)
{
    int result {0};
    while (num >= base){
        num /= base;
        ++ result;
    }
    return result;
}

// This program takes two ints as input and prints log former base latter
int main()
{
    int num {0};                                        // intialize and read in an int value to num
    cin >> num;
    int base {0};                                       // intialize and read in an int value to base
    cin >> base;

    if (num < 0 || base < 0)                            // return and print response if either the base or num are < 0
        cout << "Both inputs must be non-negative\n";
    else
        cout << log(num, base);                          // print the result of the num base base
}