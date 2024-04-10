#include <iostream>
#include <fstream>
#include <utility>

#include <algorithm>
#include <cmath>

using namespace std;

#include "binheap.h" // <- this is your modified binheap
#include "huffman.h"
#include "bitbuffer.h"

// Global arrays for prefix codes
int pcodemap[256];
int pcodelen[256];

bool operator <(const HuffmanTreeNode& x, const HuffmanTreeNode& y) {return x.freq<y.freq;}
bool operator >(const HuffmanTreeNode& x, const HuffmanTreeNode& y) {return x.freq>y.freq;}
bool operator ==(const HuffmanTreeNode& x, const HuffmanTreeNode& y) {return x.freq==y.freq;}

std::ostream& operator<<(std::ostream& os, const HuffmanTreeNode& h)
{
  return (os << "['" << h.ch << "':" << h.freq << "] " << (h.left==NULL&&h.right==NULL?"<leaf>":""));
}


// Build a Huffman tree from the given input buffer
HuffmanTreeNode* build_huffmantree(BitBuffer& input)
{
  BinHeap Q;
  size_t frequency[256];
  byte_t byte;
  int n;

  // Record the frequencies of each byte from the input
  fill(frequency,frequency+256,0);
  while(input.read_next_byte(byte)){
    frequency[byte]++;
  }

    for (int i = 0; i < 256; ++i) {
        if (frequency[i] > 0) {
            Q.insert(new HuffmanTreeNode(frequency[i], i));
        }
    }

    for(int i = 1; i <= n - 1; i++){
        // Extract the two nodes with the lowest frequency
        HuffmanTreeNode* z;
        HuffmanTreeNode* x = Q.extractMin();
        HuffmanTreeNode* y = Q.extractMin();
        z->freq = x->freq + y->freq;
        z->left = x;
        z->right = y;
        Q.insert(z);
    }

    return Q.extractMin();
}

// Create prefix codes by traversing the Huffman tree
void traverse(HuffmanTreeNode* h, int x, int depth, int total = 0)
{
  // make sure depth is not greater than we can handle
  if (depth >= 8*sizeof(int)) {
    cerr << "ERROR: tree depth is " << depth << endl;
  }

  if(!h->left && !h->right){
      pcodelen[h->ch] = x;
      pcodemap[h->ch] = total;
  }

  if(h->left){
      traverse(h->left, x + 1, depth, 2 * total);
  }

  if(h->right){
      traverse(h->right, x + 1, depth, 2 * total + 1);
  }

}


// Encode the buffer in -> out using provided Huffman tree
void huffman_encode(BitBuffer& out, BitBuffer& in, HuffmanTreeNode* h)
{
  fill(pcodelen,pcodelen+256,0); // zero length code is default    
  traverse(h,0,0);
  
  byte_t byte;
  in.reset();
  while(in.read_next_byte(byte)){
    for (int i=0; i<pcodelen[byte]; i++){
      out.write_bit(((pcodemap[byte]>>i)&1)>0);
    }
  }
}

// Decode the (Huffman coded) in buffer -> out using provided Huffman tree
void huffman_decode(BitBuffer& out, BitBuffer& in, HuffmanTreeNode* h)
{
  bool bit;
  in.reset();
  HuffmanTreeNode* ptr=h;
  while(in.read_next_bit(bit)){
    if (bit) ptr=ptr->right;
    else ptr = ptr->left;
    if (ptr==NULL) {
      cerr << "unexpected null pointer" << endl;
    }
    // Found a leaf
    if (ptr->left==NULL&&ptr->right==NULL){
      out.write_byte(ptr->ch);
      ptr = h;
    }    
  }      
}

