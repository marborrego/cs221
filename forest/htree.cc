#include <memory>
#include <list>
#include <assert.h>
#include "htree.hh"

HTree::HTree(int key, uint64_t value, tree_ptr_t left, tree_ptr_t right)
  : key_(key), value_(value), left_(left), right_(right)
{

}

int HTree::get_key() const {
  return key_;
}

uint64_t HTree::get_value() const {
  return value_;
}

HTree::tree_ptr_t HTree::get_child(Direction dir) const{
  if (dir == Direction::LEFT){
    return left_;
  }
  return right_;
}

bool HTree::key_here(int key) const {
  if (key_ == key) {return true;}
  if (left_ && left_->key_here(key)) {return true;}
  if (right_ && right_->key_here(key)) {return true;}
  return false;
}

HTree::path_t HTree::path_to(int key) const{
  path_t path;
  if (key_ == key){
    return path;
  }
  if (left_ && left_->key_here(key)){
    path = left_->path_to(key);
    path.push_front(Direction::LEFT);
    return path;
    }
  if (right_ && right_->key_here(key)){
    path = right_->path_to(key);
    path.push_front(Direction::RIGHT);
    return path;
    }
  assert(false);
}
