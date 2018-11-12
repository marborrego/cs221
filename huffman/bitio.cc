//#include <iostream>
#include "bitio.hh"
#include <cassert>
#include <math.h>

BitIO::BitIO(std::ostream* os, std::istream* is)
  : os_(os), is_(is), input_index(0), output_index(0), output_char(0), current_char(0)
{
  assert((os_ || is_)&& !(os_ && is_));    // Exactly one stream can be inputed
  if (is_){
    get_next_char();                       // Sets up the first character to read
  }
}

BitIO::~BitIO(){
  if (os_ && output_index != 0){
    *os_ << output_char;                   // Pushes the char if there was a number of bits not mod 8
  }
}

  // Output a single bit (buffered)
void BitIO::output_bit(bool bit){
  if (bit == 1){
    output_char = output_char + pow(2, output_index); // Only changes the output_char when bit is true
  }
  ++ output_index;
  if (output_index == 8){         // Pushes and resets out_put char once each bit has been accounted for
    *os_ << output_char;
    output_char = 0;
    output_index = 0;
  }
}

  // Read a single bit (or trailing zero)
bool BitIO::input_bit(){
  if (input_index == 8){          // Gets a new char once all of the bits from the last one were read
    input_index = 0;
    get_next_char();
  }
  if (current_char % 2 == 0){               // If the character is divisible by two, that means its least significant bit is a 0
    current_char = current_char >> 1;
    ++ input_index;
    return false;
  }
  current_char = current_char >> 1;
  ++ input_index;
  return true;
}

// Helper function for input_bit loads in a character from is_ to current_char
void BitIO::get_next_char(){
  is_->get(current_char);
}
