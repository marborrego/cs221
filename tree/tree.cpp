#include "tree.hh"
#include <string>
#include <assert.h>

tree_ptr_t create_tree(const key_t& key, const value_t& value, tree_ptr_t left, tree_ptr_t right){
  // the address of an int, the address of a value, a pointer to two trees
  // allocate space
  // fill parameters
  // connect to rest of tree
  tree_ptr_t leaf = new Tree({key, value, left, right});
  return leaf;
}

void destroy_tree(tree_ptr_t tree){
  if (! tree){                         // Base case of null ptr
    return;
  }
  destroy_tree(tree->left_);            // Recurses over the left side and right side
  destroy_tree(tree->right_);
  delete tree;                    // Deletes tree once both of its sides have been deleted
}

bool keyHere(tree_ptr_t tree, key_t key){
  if (tree == nullptr){
    return false;
  }
  if (tree->key_ == key){
    return true;
  }
  if (keyHere(tree->left_, key)){
    return true;
  }
  if (keyHere(tree->right_, key)){
    return true;
  }
  return false;
}

std::string path_to(tree_ptr_t tree, key_t key){
  // gives left most path to a key (ex. LRLL)
  // check left side for value, then start checking right
  // helper function for boolean response
  std::string path = "";
  if (tree->key_ == key){
    return path;
  }
  if (keyHere(tree->left_, key)){
    return "L" + path_to(tree->left_, key);
  }
  if (keyHere(tree->right_, key)){
    return "R" + path_to(tree->right_, key);
  }
  assert(false);
}
tree_ptr_t node_at(tree_ptr_t tree, std::string path){
  // follow path and return a pointer to the node containing the key
  tree_ptr_t node = tree;
  std::string L = "L";
  std::string R = "R";
  for (unsigned long i = 0; i < path.length(); i ++){
    if (path[i] == L[0]) {
      node = node->left_;
    }
    else if (path[i] == R[0]){
      node = node->right_;
    }
    else{
      assert(false);
    }
  }
  return node;
}
