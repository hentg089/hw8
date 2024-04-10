#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <cstring>

#include "bitbuffer.h"

struct HuffmanTreeNode {
  int freq;
  char ch;
  HuffmanTreeNode* left;
  HuffmanTreeNode* right;
  HuffmanTreeNode() : freq(0), ch(0), left(NULL), right(NULL) {}
  HuffmanTreeNode(int f) : freq(f), ch(0), left(NULL), right(NULL) {}
  HuffmanTreeNode(int f ,char c) : freq(f), ch(c), left(NULL), right(NULL) {}
  HuffmanTreeNode(const HuffmanTreeNode& h) : freq(h.freq), ch(h.ch), left(h.left), right(h.right) {}
};

bool operator<(const HuffmanTreeNode& x, const HuffmanTreeNode& y);
bool operator>(const HuffmanTreeNode& x, const HuffmanTreeNode& y);
bool operator==(const HuffmanTreeNode& x, const HuffmanTreeNode& y);

std::ostream& operator<<(std::ostream& os, const HuffmanTreeNode& h);

HuffmanTreeNode* build_huffmantree(BitBuffer&);
void huffman_encode(BitBuffer&, BitBuffer&, HuffmanTreeNode*);
void huffman_decode(BitBuffer&, BitBuffer&, HuffmanTreeNode*);

#endif
