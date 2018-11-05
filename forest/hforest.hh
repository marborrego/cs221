#pragma once

#include <memory>
#include <vector>
#include "htree.cc"

class HForest{
public:
  using forest_ptr_t = std::shared_ptr<HForest>;
  using tree_vec = std::vector<HTree::tree_ptr_t>;

  HForest(HForest::tree_vec trees);

  ~HForest() = default;

  double size();

  void add_tree(HTree::tree_ptr_t tree);

  HTree::tree_ptr_t pop_tree();

private:
  tree_vec trees_;
};
