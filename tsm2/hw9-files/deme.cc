/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
  : mut_rate_(mut_rate), pop_size_(pop_size)
{
  for (auto i = 0 ; pop_size ; i++){
    Chromosome chrom(cities_ptr);
    Chromosome* chrm_ptr = &chrom;
    pop_.push_back(chrm_ptr);
  }
}

// Clean up as necessary
Deme::~Deme()
{
  // Add your implementation here
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  for (auto i =0 ; pop_size_/2 ; i++){
    auto first = select_parent();
    auto second = select_parent();
    std::uniform_int_distribution<int> distribution(0, 1);
    int rand1 = distribution(generator_);
    int rand2 = distribution(generator_);
    if (rand1 < mut_rate_){
      first->Chromosome::mutate();
    }
    if (rand2 < mut_rate_){
      second->Chromosome::mutate();
    }
    auto children = first->recombine(second);
    pop_.push_back(children.first);
    pop_.push_back(children.second);
    delete children.first;
    delete children.second;
  }
  pop_.erase(pop_.begin(), pop_.begin() + (pop_size_ - 1));
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  auto best = pop_[0];
  double curr_fit, best_fit;
  curr_fit = best_fit = pop_[0]->Chromosome::get_fitness();
  for (auto chrom : pop_){
    curr_fit = chrom->Chromosome::get_fitness();
    if (curr_fit > best_fit){
      best_fit = curr_fit;
      best = chrom;
    }
  }
  return best;
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  auto tot_fit = 0;
  for (auto chrom : pop_){
    tot_fit = tot_fit + chrom -> Chromosome::get_fitness();
  }
  std::uniform_int_distribution<int> distribution(0, tot_fit - 1);
  int rand = distribution(generator_);
  auto tally = 0;
  for (auto chrom : pop_){
    if (rand < tally + chrom -> Chromosome::get_fitness()){
      return chrom;
    }
  }
}
