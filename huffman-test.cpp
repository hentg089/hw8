#include <iostream>
#include <fstream>
#include <utility>
#include <limits>
#include <cmath>

using namespace std;

#include "huffman.h"
#include "bitbuffer.h"


int main(int argc, char** argv)
{
  ifstream file;
  bool print_bitbuffers = false;
  //print_bitbuffers = true;
  
  if (argc != 2) {
    cerr << "specify file" << endl;
    exit(1);
  }

  file.open(argv[1]);

  file.ignore( std::numeric_limits<std::streamsize>::max() );
  std::streamsize length = file.gcount();
  file.clear();   //  Since ignore will have set eof.
  file.seekg( 0, std::ios_base::beg );

  BitBuffer input(length);
  BitBuffer output(length);
  BitBuffer test(length);


  while (file.good() && file.peek() != istream::traits_type::eof()){
    byte_t ch = file.get();
    input.write_byte(ch);
  }

  HuffmanTreeNode* h = build_huffmantree(input);
  
  huffman_encode(output,input,h);

  cout << "  original file: " << input.nbits() << " bits ";
  cout << "(" << input.nbits()/8 << " bytes)" << endl;
  cout << "compressed file: " << output.nbits() << " bits ";
  cout << "(~" << int(ceil(output.nbits()/8.0)) << " bytes)" << endl;
  cout << "compression ratio: " << (double)input.nbits()/(double)output.nbits();
  cout << " (" << 100*(1.0-(double)output.nbits()/(double)input.nbits()) << "%)" << endl;

   
  cout << "testing decode..." << endl;

  huffman_decode(test,output,h);

  if (print_bitbuffers){
    cout << "--- INPUT ---" << endl;
    cout << input;
    cout << "--- ENCODED ---" << endl;
    cout << output;
    cout << "--- DECODED ---" << endl;
    cout << test;    
  }
  
  if (test==input){
    cout << "Decoding successful!" << endl;
  }
  else {
    cout << "Decoding failed" << endl;
  }      
}
