/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"
#include "iostream"
#include "cassert"

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
  : mut_rate_(mut_rate), pop_size_(pop_size)
{
  for (unsigned i = 0 ; i<pop_size ; i++){
    Chromosome* chrom = new Chromosome(cities_ptr);
    pop_.push_back(chrom);
  }
}

// Clean up as necessary
Deme::~Deme()
{
  for (Chromosome* chrom : pop_){
    delete chrom;
  }
  // Looop and delete pointers
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
  std::vector<Chromosome*> new_gen;
  for (unsigned i =0 ; i<pop_size_/2 ; i++){
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
    new_gen.push_back(children.first);
    new_gen.push_back(children.second);
  }
  for (Chromosome* chrom : pop_){
    delete chrom;
  }
  pop_ = new_gen;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  Chromosome* best = pop_[0];
  double curr_fit, best_fit;
  curr_fit = best_fit = pop_[0]->get_fitness();
  for (auto chrom : pop_){
    curr_fit = chrom->get_fitness();
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
  double tot_fit = 0;
  for ( Chromosome* chrom : pop_){
    double fitness = chrom->get_fitness();
    tot_fit += fitness;
  }
  // std::cout<<"TOTAL Fitness:::::"<<tot_fit<<std::endl;
  std::uniform_int_distribution<double> distribution(0, tot_fit);
  double rand = distribution(generator_);
  double tally = 0;
  for (Chromosome* chrom : pop_){
    double chrom_fitness = chrom->get_fitness();
    tally += chrom_fitness;
    if (rand < tally){
      return chrom;
    }
  }
  assert(false);
  return nullptr;
}
