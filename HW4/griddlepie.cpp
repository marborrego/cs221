#include <iostream>
#include <cmath>

bool pyth(unsigned point1, unsigned point2, unsigned dimension)
    {
        if (std::hypot(point1, point2) <= dimension)
            return true;
        else
            return false;
    }

double in_circle(unsigned points)
{
    double in_circ = 0;                 // This is a counter for the points that fall within the unit circle
    for (unsigned l = 0; l < points; ++l){       // Loops through the length of the square
        for (unsigned w = 0; w < points; ++w){       // Loops through the width of the square
            if (pyth(l, w, points))    // If the point is within the unit circle, include it
                ++in_circ;
        }
    }
    return in_circ;
}

// This function returns an estimate of pi
double gridpi(unsigned npoints)
{
    double total = npoints * npoints;   // This is the amount of points in the square
    double points_in = in_circle(npoints);
    double pi = (points_in / total) * 4;
    return pi;

}

// This program prints an estimate of pi by comparing the number of points on a grid that are within a circle
int main()
{
    unsigned input = 0;
    std::cin >> input;
    std::cout << gridpi(input);
    return 0;
}
