/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include <iostream>

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size()))
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  int size = order_.size();
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, size - 1); // define the range
  int g1 = distr(eng);
  int g2 = distr(eng);
  while (g1 == g2){
    g2 = distr(eng);
  }
  int temp = order_[g1];
  order_[g1] = order_[g2];
  order_[g2] = temp;

  assert(is_valid());
}

int Chromosome::get_size(){
  return get_ordering().size();
}
//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  std::pair<Chromosome*, Chromosome*> children;
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, cities_ptr_->size() - 1); // define the range
  unsigned b = distr(eng);
  unsigned e = distr(eng);
  while (e < b ){
    b = distr(eng);
    e = distr(eng);
  }

  children.first = create_crossover_child(this, other, b, e);
  children.second = create_crossover_child(other, this, b, e);
  assert(is_valid());
  assert(other->is_valid());
  return children;

  // Add your implementation here
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < p2->order_.size());
      child->order_[i] = p2->order_[j];
      j++;
    }
  }
  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double total_dist = cities_ptr_->Cities::total_path_distance(order_);
  return (1/total_dist);
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{
  const unsigned int size = order_.size();
  for(unsigned i = 0; i < size; i++) { // Check each other number in the array
    for(unsigned int j = i + 1; j < size; j++) { // Check the rest of the numbers
        if(order_[i] == order_[j]) {
          return false;
              }
        } // Comparison loop
    }
    if (size != cities_ptr_->size()){
      return false;
    }
    return true;// Main check loop
  }

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  for (unsigned i = begin ; i < end; i++){
    if (order_[i] == value){
      return true;
    }
  }
  return false;
}
