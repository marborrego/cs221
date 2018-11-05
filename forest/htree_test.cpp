#include <memory>
#include <list>
#include <iostream>
#include <vector>
#include "htree.cc"

// Building a tree to run tests on
HTree::tree_ptr_t a(new HTree::HTree(6, 13));

HTree::tree_ptr_t c(new HTree::HTree(12, 17));

HTree::tree_ptr_t b(new HTree::HTree(-5, 14, c, a));

HTree::tree_ptr_t d(new HTree::HTree(3, 76));

HTree::tree_ptr_t e(new HTree::HTree(12, 3, d, nullptr));

HTree::tree_ptr_t first(new HTree::HTree(126, 0, b, e));

// Tests get value
void test_gv(){
  if (a->get_value() != 13){
    std::cout << "get_value failed \n";
  }
  else if (b->get_value() != 14){
    std::cout << "get_value failed \n";
  }
  else if (c->get_value() != 17){
    std::cout << "get_value failed \n";
  }
  else if (d->get_value() != 76){
    std::cout << "get_value failed \n";
  }
  else if (e->get_value() != 3){
    std::cout << "get_value failed \n";
  }
  else if (first->get_value() != 0){
    std::cout << "get_value failed \n";
  }
  else {
    std::cout << "get_value success \n";
  }
}

// Tests get_key
void test_gk(){
  if (a->get_key() != 6){
    std::cout << "get_key failed \n";
  }
  else if (b->get_key() != -5){
    std::cout << "get_key failed \n";
  }
  else if (c->get_key() != 12){
    std::cout << "get_key failed \n";
  }
  else if (d->get_key() != 3){
    std::cout << "get_key failed \n";
  }
  else if (e->get_key() != 12){
    std::cout << "get_key failed \n";
  }
  else if (first->get_key() != 126){
    std::cout << "get_key failed \n";
  }
  else {
    std::cout << "get_key success \n";
  }
}

// Tests get_child
void test_gc(){
  if (a->get_child(HTree::Direction::LEFT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (b->get_child(HTree::Direction::LEFT) != c){
      std::cout << "get_child failed \n";
    }
  else if (c->get_child(HTree::Direction::LEFT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (d->get_child(HTree::Direction::LEFT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (e->get_child(HTree::Direction::LEFT) != d){
      std::cout << "get_child failed \n";
    }
  else if (first->get_child(HTree::Direction::LEFT) != b){
      std::cout << "get_child failed \n";
    }
  if (a->get_child(HTree::Direction::RIGHT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (b->get_child(HTree::Direction::RIGHT) != a){
      std::cout << "get_child failed \n";
    }
  else if (c->get_child(HTree::Direction::RIGHT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (d->get_child(HTree::Direction::RIGHT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (e->get_child(HTree::Direction::RIGHT) != nullptr){
      std::cout << "get_child failed \n";
    }
  else if (first->get_child(HTree::Direction::RIGHT) != e){
      std::cout << "get_child failed \n";
    }
    else {
      std::cout << "get_child success \n";
    }
  }

// Main runs tests
int main(){
  test_gv();
  test_gk();
  test_gc();
}
