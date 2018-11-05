#include <memory>
#include <list>
#include <assert.h>
#include "htree.hh"

// Contructor initializes inputs
HTree::HTree(int key, uint64_t value, tree_ptr_t left, tree_ptr_t right)
  : key_(key), value_(value), left_(left), right_(right)
{

}
// Returns key
int HTree::get_key() const {
  return key_;
}

// Returns value
uint64_t HTree::get_value() const {
  return value_;
}

// Returns either the left or right child to node
HTree::tree_ptr_t HTree::get_child(Direction dir) const{
  if (dir == Direction::LEFT){                   // Becuase of the use of Direction, there are only two possible input cases
    return left_;
  }
  return right_;
}

// Helper function for path_t that checks if the key exists in the tree
bool HTree::key_here(int key) const {
  if (key_ == key) {return true;}
  if (left_ && left_->key_here(key)) {return true;}   // Have to check that left_ exists otherwise left_->key_ wont exist
  if (right_ && right_->key_here(key)) {return true;} // Have to check that right_ exists otheriwse right_->key_ wont exist
  return false;
}

// Returns a path (left and right) to the key input
HTree::path_t HTree::path_to(int key) const{
  path_t path;
  if (key_ == key){                       // Returns an empty list if the first node has that key
    return path;
  }
  if (left_ && left_->key_here(key)){     // Checking if there is a left side and if it contains the key
    path = left_->path_to(key);           // Recurses over left side to find key
    path.push_front(Direction::LEFT);     // Because of the recursive nature, the direction is added to the front
    return path;
    }
  if (right_ && right_->key_here(key)){   // Checking if there is a left side and if it contains the key
    path = right_->path_to(key);          // Recurses over right side to find key
    path.push_front(Direction::RIGHT);    // Because of the recursive nature, the direction is added to the front
    return path;
    }
  assert(false);                          // Crashes if the key doesnt exist
}
