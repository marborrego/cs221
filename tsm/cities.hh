/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>


class Cities {
 public:

  Cities();
  ~Cities() = default;
  
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;
  using cities = std::vector<Cities::coord_t>;
  using permutation_t = std::vector<unsigned int>;

  // Add a city's coordinates to the city vector
  void add_coord(coord_t coord);
  // Reorders the coordinates based on the ordering of elements
  Cities reorder(const permutation_t& ordering) const;
  // Randomly reorders the elements of the permutation vector
  permutation_t random_permutation(unsigned len);
  // Public access to the cities list
  cities get_cities();
  // Calculates the distance to go to every city, returning to the first
  double total_path_distance(const permutation_t& ordering) const;


 private:
  // Calculates distance between two coordinates
  double distance_calc(Cities::coord_t first, Cities::coord_t second) const;
  // Variable of cities
  cities cities_;


};

std::istream& operator>> (std::istream& in, Cities& city);

std::ostream& operator<< (std::ostream& out, Cities& city);
