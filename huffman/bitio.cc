#include <iostream>
#include "bitio.hh"

  // Construct with one of either an input stream or output (the other null)
BitIO(std::ostream* os, std::istream* is){
  assert((os || is)&& !(os && is));
  os_(os);
  is_(is);
}

  // Flushes out any remaining output bits and trailing zeros, if any:

  // Output a single bit (buffered)
void output_bit(bool bit){
  os_ << 
}

  // Read a single bit (or trailing zero)
bool input_bit(){
  is_ >> 
}
