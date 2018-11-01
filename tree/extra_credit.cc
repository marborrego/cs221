#include <iostream>
#include <cassert>

struct LNode {
  int data_;
  LNode* next_;
};

//////////////////////////////////////////////////////////////////////////////
void print_list(const LNode* head)
{
  while (head) {
    std::cout << head->data_ << " ";
    head = head->next_;
  }
  std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
// Reverse a list iteratively
LNode*
reverse_list(LNode* head)
{
  if (! head){
    return head;
  }
  auto next_save = head->next_;  // Next save points to head->next
  head->next_ = nullptr;         // First head->next now points to nullptr
  auto prev_save = head;         // prev_save points to the head
  head = next_save;              // head now points to next_save
  while (head->next_){
    next_save = head->next_;
    head->next_ = prev_save;
    prev_save = head;
    head = next_save;
  }
  head->next_ = prev_save;
  return head;
}

//////////////////////////////////////////////////////////////////////////////
// Reverse a list recursively

// Helper function reverses the order of next_ pointers
LNode* recursive_helper(LNode* head){
  if (! head->next_ || ! head){
    return head;
  }
  else{
    auto rev_next = recursive_helper(head->next_);
    rev_next->next_ = head;
    return head;
  }

}
LNode*
reverse_list_r(LNode* head)
{
  auto last = head;                                 // Need to keep track of the last node because we will want to return it as the first
  while(last->next_){
    last = last->next_;
  }
  auto after_first = recursive_helper(head->next_); // Recursively reorders everything but the first node
  after_first->next_ = head;                        // We need to separately re-add head because the recursive function is unable to make a specific element point to nullptr
  head->next_ = nullptr;
  return last;
}

////////////////////////////////////////////////////////////////////////////// 
int main()
{
  LNode* last = new LNode({4, nullptr});
  LNode* third = new LNode({3, last});
  LNode* second = new LNode({2, third});
  LNode* first = new LNode({1, second});
  print_list(first);
  auto reversed = reverse_list(first);
  print_list(reversed);
  auto back = reverse_list_r(reversed);
  print_list(back);
  auto head = first;
  while (head){
    auto next = head->next_;
    delete head;
    head = next;
  }
}
