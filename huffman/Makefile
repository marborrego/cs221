CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  test_bitio test_hforest test_huffman encode decode

test_bitio: bitio.o test_bitio.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_htree: test_htree.o htree.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_huffman: test_huffman.o huffman.o hforest.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_hforest: test_hforest.o hforest.o
	$(CXX) $(LDFLAGS) -o $@ $^

encode: encode.o bitio.o huffman.o hforest.o
	$(CXX) $(LDFLAGS) -o $@ $^

decode: decode.o  bitio.o huffman.o hforest.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o test_bitio encode decode

test: all
	./test_hforest
	./test_huffman
	./test_bitio
