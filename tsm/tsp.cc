#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include "cities.hh"

int main(int argc, char *argv[]){
  for (int i = 1; i < argc; i++){                                                    // Allows for multiple files to be read
    std::ifstream infile {argv[i]};
    assert(infile);
    std::ofstream outfile {"shortest.tsv"};
    assert(outfile);

    Cities city;
    infile >> city;
    double best_dist = std::numeric_limits<double>::infinity();
    for (int i = 0; i < 1000000; i++){
      Cities::cities city_vec = city.get_cities();
      unsigned len = city_vec.size();
      Cities::permutation_t permutation = city.random_permutation(len);
      double this_dist = city.total_path_distance(permutation);
      if (this_dist < best_dist){
        best_dist = this_dist;
        city = city.reorder(permutation);
        std::cout << double(i) << " " << int(best_dist) << "\n";
      }
    }
    outfile << city;
    infile.close();
    outfile.close();
  }
  return 0;
}
