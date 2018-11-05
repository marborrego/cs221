#include <iostream>
#include "hforest.cc"
#include <vector>

// Making of trees and forest
HTree::tree_ptr_t a(new HTree::HTree(6, 13));

HTree::tree_ptr_t c(new HTree::HTree(12, 17));

HTree::tree_ptr_t b(new HTree::HTree(-5, 14, c, a));

HTree::tree_ptr_t d(new HTree::HTree(3, 76));

HTree::tree_ptr_t e(new HTree::HTree(12, 3, d, nullptr));

HTree::tree_ptr_t first(new HTree::HTree(126, 0, b, e));

HTree::tree_ptr_t add_this(new HTree::HTree(13, 4));


HForest::tree_vec trees = {a, b, c , d, e, first};
HForest::forest_ptr_t f_ptr(new HForest::HForest(trees));
HForest::tree_vec empty = {};
HForest::forest_ptr_t e_ptr = trees;


// Tests the members of HForest using the above trees/forest
int main(){
  auto s = f_ptr->size();
  std::cout << "Forest size is "<< s << " trees \n";
  s = empty->size();
  std::cout << "Empty forest is " << s << "\n";

  f_ptr->add_tree(add_this);
  s = f_ptr->size();
  std::cout << "New size is " << s << "\n";

  auto popped = f_ptr->pop_tree();
  std::cout << "Popped has value of " << popped->get_value() << "\n";

  popped = f_ptr->pop_tree();
  std::cout << "Popped has value of " << popped->get_value() << "\n";

  s = f_ptr->size();
  std::cout << "New size is " << s << "\n";
}
