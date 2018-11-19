#include <vector>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <cassert>
#include "cities.hh"

int main(int argc, char *argv[]){
  for (int i = 1; i < argc; i++){                                                    // Allows for multiple files to be read
    std::ifstream infile {argv[i]};
    assert(infile);
    std::ofstream outfile {"shortest.tsv"};                                          // The shortest path found will be outputted as ordered coordinates 
    assert(outfile);

    Cities city;
    infile >> city;                                                                  // Stream in cordinates of cities
    double best_dist = std::numeric_limits<double>::infinity();                      // The best distance is initialized to infinity so any distance is better
    for (int i = 0; i < 1000000; i++){                                               // This is the main part of the program, where the coordinates are randomly ordered and the distance is measured. The shortest distance is saved and outputted.
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
