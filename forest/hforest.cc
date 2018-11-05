#include <memory>
#include <vector>
#include <algorithm>
#include "hforest.hh"

HForest::HForest(HForest::tree_vec trees)
  : trees_(trees)
{
  
}
double HForest::size() {
  return trees_.size();
}

void HForest::add_tree (HTree::tree_ptr_t tree){
  trees_.push_back(tree);
}

bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
  return t1->get_value() < t2->get_value();
}

HTree::tree_ptr_t HForest::pop_tree(){
  if (trees_.size() == 0){
    return nullptr;
  }
  std::make_heap(trees_.begin(), trees_.end(), compare_trees);
  std::pop_heap(trees_.begin(), trees_.end());
  auto largest = trees_.back();
  trees_.pop_back();
  return largest;
}
