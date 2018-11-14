#include <climits>
#include <vector>
#include <iostream>

#include "htree.hh"
#include "hforest.hh"
#include "huffman.hh"

  using bits_t = std::vector<bool>;

  Huffman::Huffman(){ 
    freqs = freqs;
    for ( int i=0; i<Huffman::ALPHABET_SIZE; i++){ // fill freqs table with zeroes
      freqs.vector::push_back(0);
    }
    forest = Huffman::forest;
    huff_tree = Huffman::huff_tree;
    decode_node = Huffman::decode_node;

  }

  void Huffman::build_forest(){
    forest.pop_top(); // remove any previous tree from the forest
    for (int i=0; i<Huffman::ALPHABET_SIZE; i++){
      forest.add_tree(HTree::tree_ptr_t(new HTree(i, freqs.vector::at(i)))); // add each element of freqs as tree with index as key, freq as value
    }
  }
  void Huffman::build_huff_tree(){
    while (forest.HForest::size() > 1){
      HTree::tree_ptr_t t1 = forest.HForest::pop_top(); // get 2 lowest valued trees from forest & remove them
      HTree::tree_ptr_t t2 = forest.HForest::pop_top();
      HForest::tree_t t3 = HForest::tree_t(new HTree(-1, (t1->get_value()+t2->get_value()), t1, t2)); // add back in a tree with the first two trees as children, -1 as key, sum of children's values as value
      forest.HForest::add_tree(t3);
      huff_tree = t3; // set the huff_tree to be this new tree each time, will end up being the huff tree when build is done
    }
  }

  bits_t Huffman::path_to_bools(HTree::path_t path){
    bits_t path_bits; 
    for ( HTree::Direction x : path){  // loop for each item in path
      if (x == HTree::Direction::LEFT){
        path_bits.push_back(false); // if its left add false
      }
      else{
        path_bits.push_back(true); // if its right add true
      }
    }
    return path_bits;
  }





  // Encode a symbol into a sequence of bits, then update frequency table.
  bits_t Huffman::encode(int symbol){
    build_forest();
    build_huff_tree();
    assert(forest.size() == 1);
    // std::cout << "symbol:  " << symbol << "\n";
    HTree::path_t path = huff_tree->path_to(symbol);
    // std::cout << "path length:  " << path.size() << "\n";
    bits_t path_bits = path_to_bools(path);
    // for ( bool bit : path_bits){
      // std::cout << bit;
        // std::cout<< "\n";
    freqs.vector::at(symbol) += 1;
    return path_bits;
  }

  // Decode a single bit into a symbol. If no symbol can be unmabiguously decoded
  // without additional bits, returns a negative value.
  // Subsequent calls with more bits should eventually resolve to either
  // a character symbol or HEOF.
  // Finally, updates the frequency table with this additional symbol.
  int Huffman::decode(bool bit){
    HForest::tree_t next_t;
    if (!decode_node){  // if this is the first time, construct the forest and tree from scratch
      build_forest();
      build_huff_tree();
      decode_node = huff_tree; // set decode node to the root of the huffman tree
    }
      if (bit == false){
        next_t = decode_node->get_child(HTree::Direction::LEFT); // set the decode node to the left child
      }
      else if (bit == true){
        next_t = decode_node->get_child(HTree::Direction::RIGHT); // set the decode node to the right child 
      }
      if (next_t->get_key() == -1){ // if the node we're at is not a leaf, return -1
        decode_node = next_t;
        return -1;
      }
      else{ // else update the frequency in freqs, rebuild tree, reset decode node to root 
        freqs.vector::at(next_t->get_key()) += 1; 
        build_forest();
        build_huff_tree();
        decode_node = huff_tree;
        return next_t->get_key(); // return the character at the leaf
      }
    }









