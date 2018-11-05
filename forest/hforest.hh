#pragma once

#include <memory>
#include <vector>
#include "HTree.hh"

class HForest{
public:
  using forest_ptr_t = std::shared_ptr<const HForest>;
  using tree_list = std::vector<HTree::tree_ptr_t>;

  HForest(tree_list trees);

  ~HForest() = default;

  double size();

  void add_tree(HTree::tree_ptr_t tree);

  HTree::tree_ptr_t pop_tree();

private:
  tree_list trees_;
};
