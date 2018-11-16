/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>


// Representation of an ordering of cities
class Cities {
 public:

  Cities();
  ~Cities() = default;
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  using cities = std::vector<Cities::coord_t>;

  void add_coord(coord_t coord);

  // An ordering of the cities in cities_t. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  permutation_t random_permutation(unsigned len);


  cities get_cities();
  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;


 private:
  double distance_calc(Cities::coord_t first, Cities::coord_t second) const;

  cities cities_;


};

std::istream& operator>> (std::istream& in, Cities& city);

std::ostream& operator<< (std::ostream& out, Cities& city);