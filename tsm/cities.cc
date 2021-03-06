#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "cities.hh"

Cities::Cities(){
  cities_ = cities_;
}

double Cities::distance_calc(Cities::coord_t first, Cities::coord_t second) const {
return sqrt(pow((first.first - second.first), 2) + pow((first.second - second.second), 2));
}

Cities Cities::reorder(const permutation_t& ordering) const{
  int perm_len = ordering.size();
  Cities new_city;
  for (int i=0; i<perm_len; i++){                         // This takes the order of ordering and creates a list of coordinates based on cities_
    new_city.cities_.push_back(cities_[ordering[i]]);
  }
  return new_city;
}
void Cities::add_coord(Cities::coord_t coord){
  cities_.push_back(coord);
}

Cities::cities Cities::get_cities(){
  return cities_;
}

Cities::permutation_t Cities::random_permutation(unsigned len){
  Cities::permutation_t perm (len);
  for (unsigned i = 0; i < len; i++){
    perm[i] = i;                        // This creates a list of ordered elements so that they can be rearranged
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(perm.begin(), perm.end(), g);   // This randomly rearranges the numbers so a new permutation of city order can be tried.
  return perm;

}

double Cities::total_path_distance(const Cities::permutation_t& ordering) const {
  double distance = 0;
  double len = ordering.size()-1; // The last city is a special case because it needs to connect to the first city
  for (double i = 0; i < len; i ++){
    distance += distance_calc(cities_[ordering[i]], cities_[ordering[i+1]]);
  }
  distance += distance_calc(cities_[ordering[0]], cities_[ordering.size()-1]); // Need to return to first city
  return distance;
}

std::istream& operator>> (std::istream& in, Cities& city){
  Cities::coord_t cord;
  int x;
  int y;
  while(in >> x >> y){  // Allows both x and y to be streamed in and paired
    cord.first = x;
    cord.second = y;
    city.add_coord(cord);
  }
  return in;
}

std::ostream& operator<< (std::ostream& out, Cities& city){
  Cities::cities city_vec = city.get_cities();
  for (Cities::coord_t cord : city_vec){
    out << cord.first << "\t" << cord.second << "\n";
  }
  return out;
}

