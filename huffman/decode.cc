#include <fstream>

#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char *argv[]){
    for ( int i = 1; i< argc ; i++){  // loops through each argument in the command line
        std::ifstream infile {argv[i]}; // initialize ifstream with filename
        std::string infile_name = argv[i]; // record infilename so we can name the outfile
        assert(infile);
        std::string outfile_name = infile_name + ".plaintext";  // name the outfile
        std::ofstream outfile{outfile_name};  // initialize ofstream with outfilename
        assert(outfile);
        Huffman huffman; 
        BitIO bitio(nullptr, &infile); // initialize bitio with infile 
        int symbol = 0;
        while (symbol != Huffman::HEOF){ // loop while current symbol is not EOF
            symbol = -1;  // reset the symbol every time the loop runs
            while (symbol == -1){  // keep doing this until the symbol is an actual character
                bool bit = bitio.input_bit();  // call bitio to read in single bit
                symbol = huffman.decode(bit);  // decode that bit      
            }
            char symbol1 = symbol; 
            outfile << symbol1;  // push symbol to outfile
        }
        infile.close();
        outfile.close();
    }
    return 0;
}
