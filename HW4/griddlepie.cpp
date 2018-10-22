#include <iostream>
#include <cmath>

// This function compares the distance of (point1, point2) from the origin to the dimension
bool pyth(unsigned point1, unsigned point2, unsigned dimension)
    {
      return (std::hypot(point1, point2) <= dimension);
    }
// This function loops through every point to determine if it is within the unit circle
double in_circle(unsigned points)
{
    double in_circ = 0;                          // This is a counter for the points that fall within the unit circle
    for (unsigned l = 0; l < points; ++l){       // Loops through the length of the square
        for (unsigned w = 0; w < points; ++w){   // Loops through the width of the square
            if (pyth(l, w, points))              // If the point is within the unit circle, include it
                ++in_circ;
        }
    }
    return in_circ;
}

// This function returns an estimate of pi
double gridpi(unsigned npoints)
{
    double total = npoints * npoints;        // This is the amount of points in the square
    double points_in = in_circle(npoints);   // Calls in_circle function to calculate the amount of points one quadrant of the unit circle
    double pi = (points_in / total) * 4;     // Pi is equal to the number of points in the quadrant divided by the total amount of points times four
    return pi;

}

// This program prints an estimate of pi by comparing the number of points on a grid that are within a circle
int main()
{
  //unsigned input = 0;           // This is a variable that will hold the input value
  //std::cin >> input;            // Asks for input
  //std::cout << gridpi(input);   // Calls gridpi and outputs the return value
  std::cout << gridpi(100000);
  return 0;
}
