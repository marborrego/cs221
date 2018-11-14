#include <fstream>
#include <cctype>

#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char *argv[]){
    for ( int i = 1; i< argc ; i++){  // loop for each argument in command line
        std::ifstream infile {argv[i]};  // initialize ifstream with infile
        std::string infile_name = argv[i]; 
        assert(infile);
        std::string outfile_name = infile_name + ".comp";
        std::ofstream outfile {outfile_name}; // initialize ofstream with outfile
        assert(outfile);
        char symbol = -1;
        Huffman huffman; // initialize huff
        BitIO bitio(&outfile, nullptr); // initialize bitio with ofstream 
        while (infile.get(symbol)){  // checks if file has another byte, assigns byte to symbol if it does
            Huffman::bits_t bools_list = huffman.encode(symbol);  // get list of bools from symbol
            for (bool bool_t : bools_list){
                bitio.output_bit(bool_t); // for each bool in list, output it using bitio
            }

        }
        Huffman::bits_t EOF_asboollist = huffman.encode(Huffman::HEOF);  //add the EOF

        for (bool bool_heof : EOF_asboollist){
            std::cout << bool_heof << "\n";
            bitio.output_bit(bool_heof);

    }
    infile.close();
    outfile.close();
    }
return 0;
}


