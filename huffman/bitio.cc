#include <iostream>
#include "bitio.hh"
#include <cassert>
#include <math.h>

BitIO::BitIO(std::ostream* os, std::istream* is)
  : os_(os), is_(is), input_index(0), output_index(7), output_char(0), current_char(get_next_char())
{
  assert((os_ || is_)&& !(os_ && is_));
}

  // Flushes out any remaining output bits and trailing zeros, if any:

  // Output a single bit (buffered)
void BitIO::output_bit(bool bit){
  if (bit == 1){
    output_char = output_char + pow(2, output_index);
  }
  -- output_index;
  if (output_index == -1){
    *os_ << output_char;
    output_index = 7;
  }
}

  // Read a single bit (or trailing zero)
bool BitIO::input_bit(){
  if (input_index == 8){
    input_index = 0;
    get_next_char();
  }

}

int BitIO::get_next_char(){
  *is_ >> current_char;
}
