#include <string>
#include <iostream>
#include "tree.hh"
#include "tree.cpp"

// Use this to create a tree that you want to test on
tree_ptr_t create(){
    tree_ptr_t last = create_tree(9, 12, nullptr, nullptr);
    tree_ptr_t a = create_tree(6, 13, last, nullptr);
    tree_ptr_t c = create_tree(12, 17, nullptr, nullptr);
    tree_ptr_t b = create_tree(-5, 14, c, a);
    tree_ptr_t d = create_tree(3, 76, nullptr, nullptr);
    tree_ptr_t e = create_tree(12, 3, d, nullptr);
    tree_ptr_t first = create_tree(126, 0, b, e);
    return first;
}
// destroy_tree tested using valgrind
void test_path(tree_ptr_t tree){
  if (path_to(tree, 9) != "LRL"){
    std::cout << "Path to failure 1" << path_to(tree, 9) << "\n";
  }
  else if (path_to(tree, 3) != "RL"){
    std::cout << "Path to failure 2" << path_to(tree, 3) << "\n";
  }
  else if (path_to(tree, 126) != ""){
  std::cout << "Path to failure 3" << path_to(tree, 126) << "\n";
  }
  else if (path_to(tree, 12) != "LL"){
    std::cout << "Path to failure 4" << path_to(tree, 12)<< "\n";
  }
  else{
    std::cout << "Path to success \n";
  }
}

void test_node(tree_ptr_t tree){
  if (node_at(tree, "LRL") != tree->left_->right_->left_){
    std::cout << "Node at Failure 1 \n";
  }
  else if (node_at(tree, "LR") != tree->left_->right_){
    std::cout << "Node at Failure 2 \n";
  }
  else if (node_at(tree, "") != tree){
    std::cout << "Node at failure 3 \n";
  }
  else{
    std::cout << "Node at success \n";
  }
}
int main(){
  tree_ptr_t test_tree = create();
  test_path(test_tree);
  test_node(test_tree);
  test_destroy(test_tree);
}
