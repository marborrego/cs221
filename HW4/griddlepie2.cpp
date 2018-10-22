#include <iostream>
#include <cmath>

// This function takes the length of two sides and checks if the hypotenus is less than or equal to a given length
constexpr bool pyth(unsigned point1, unsigned point2, unsigned dimension)
{
  return (point1 * point1 + point2 * point2 <= dimension * dimension);
}

// This function takes the dimension of a square as input and checks how many points are within the unit circle
constexpr double in_circle(unsigned points)
{
  double in_circ = 0;                             // This is a counter for the points that fall within the unit circle
  for (unsigned l = 0; l < points; ++l){          // Loops through the length of the square
    for (unsigned w = 0; w < points; ++w){        // Loops through the width of the square
      if (pyth(l, w, points))                     // If the point is within the unit circle, include it
        ++in_circ;
    }
  }
  return in_circ;                                 // Returns the amount of points in the circle
}

// This function returns an estimate of pi
constexpr double gridpi(unsigned npoints)
{
  const double total = npoints * npoints;         // This is the amount of points in the square
  const double points_in = in_circle(npoints);    // Calls in_circle to calculate the amount of points within one quadrant of the unit circle
  const double pi = (points_in / total) * 4;      // Pi is the amount of points with the unit circle divided by the all point in the unit square
  return pi;
}

// This program prints an estimate of pi by comparing the number of points on a grid that are within a circle
int main()
{
  unsigned input = 0;               // Creates a variable that will hold the value of the input
  std::cin >> input;                // Asks for input
  double result = gridpi(input);    // Calls gridpi on the input
  std::cout << result;              // Returns result of gridpi
  return 0;
}
