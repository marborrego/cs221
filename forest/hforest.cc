#include <memory>
#include <vector>
#include <algorithm>
#include "hforest.hh"

HForest::HForest(HForest::tree_vec trees)
  : trees_(trees)
{
  
}

//returns number of trees in the vector
double HForest::size() {     // Relies on std::vector built_in size()
  return trees_.size();
}

// Adds a new tree to the end of the vector
void HForest::add_tree (HTree::tree_ptr_t tree){
  trees_.push_back(tree);         // Relies on std::vector built_in push_bak()
}

// Helper function for tree_ptr_to
bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
  return t1->get_value() < t2->get_value();          // Trees are ordered by the size of their value, with the hghest valued tree being the root
}

// Removes and returns the tree containing the highest value
HTree::tree_ptr_t HForest::pop_tree(){
  if (trees_.size() == 0){               // Cant pop anything if the vector is empty
    return nullptr;
  }
  std::make_heap(trees_.begin(), trees_.end(), compare_trees); // Lazy-order of vector makes the first tree the one with the highest value
  std::pop_heap(trees_.begin(), trees_.end());                 // Places the largest valued tree last
  auto largest = trees_.back();                                // saves the largest valued tree
  trees_.pop_back();                                           // removes the largest valued tree
  return largest;
}
