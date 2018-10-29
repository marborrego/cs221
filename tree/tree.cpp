#include "tree.hh"
#include <string>
#include <assert.h>

// Create a leaf to a tree by allocating memory and returning a pointer to where inputed values are stored
tree_ptr_t create_tree(const key_t& key, const value_t& value, tree_ptr_t left, tree_ptr_t right){
  tree_ptr_t leaf = new Tree({key, value, left, right});     // Creates a tree and a pointer to that tree which will be the only way to reference it
  return leaf;
}

// Frees the space in memory where the tree was stored
void destroy_tree(tree_ptr_t tree){
  if (! tree){                           // The function will stop recursively calling itself when its at the bottom-most leaf
    return;
  }
  destroy_tree(tree->left_);            // Deletes everything left of the leaf
  destroy_tree(tree->right_);           // Deletes everything right of the leaf
  delete tree;                          // Once all of the sub branches are deleted, the leaf can be deleted
}

// Helper function for path_to that returns a boolean based on if the value exists in the tree
bool keyHere(tree_ptr_t tree, key_t key){
  if (tree == nullptr){                  // The key is not in the tree if the tree is nullptr
    return false;
  }
  if (tree->key_ == key){                // The key is in the tree if the ptr points to the tree containing that value
    return true;
  }
  if (keyHere(tree->left_, key)){        // Check all the left side of the tree for the value
    return true;
  }
  if (keyHere(tree->right_, key)){       // Check all of the right side of the tree for value
    return true;
  }
  return false;                          // If the key is never found, it is not in the tree
}

// Returns a string of "L" and "R" based on where a key is in the tree. Crashes if other chars are used.
std::string path_to(tree_ptr_t tree, key_t key){
  std::string path = "";
  if (tree->key_ == key){                        // The function returns "" if the first leaf of the tree holds the key
    return path;
  }
  if (keyHere(tree->left_, key)){                // Add "L" tot he return string if the key is on the left side
    return "L" + path_to(tree->left_, key);
  }
  if (keyHere(tree->right_, key)){               // Add "R" to the return string if the key is in the right side of the tree
    return "R" + path_to(tree->right_, key);
  }
  assert(false);                                 // Crash if char in string is not "L" of "R"
}

// Finds what node is at the inputed path
tree_ptr_t node_at(tree_ptr_t tree, std::string path){
  std::string L = "L";                                    // These are just string variables so that they are the same type as path
  std::string R = "R";
  for (unsigned long i = 0; i < path.length(); i ++){     // Loops through every char in the string
    if (path[i] == L[0]) {                                // Moves pointer left if the char is L
      if (tree->left_ == nullptr){                        // Prevents the code from trying to use nullptr as a tree
        return nullptr;
      }
      tree = tree->left_;
    }
    else if (path[i] == R[0]){                            // Moves pointer right if the char is R
      if (tree->right_ == nullptr){                       // Prevents the code from trying to use nullptr as a tree
        return nullptr;
      }
      tree = tree->right_;
    }
    else{                                                 // Returns null pointer if any character other than "L" or "R" is used
      return nullptr;
    }
  }
  return tree;
}
