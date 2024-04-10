#ifndef BINHEAPH
#define BINHEAPH

// binheap.h - declaration file for Binary Heap structure

#include <iostream>
#include "huffman.h"

using namespace std ;

typedef HuffmanTreeNode* KeyType ;   // The type of the key items in the heap

class BinHeap {
// Utility routines that need to access data members 
   void minHeapify( int i ) ; 
   void buildMinHeap(int n) ; 

public:
// Class member variables
   KeyType* A ;  // Only needs to be public for heap-sort
   int heapSize ; // Should use accessors/mutators, but easier to code
   int length ;   // May be useful for implementing heap-sort

// Constructors, Destructor
   BinHeap() ;
   BinHeap( int arrayLength ) ;
   ~BinHeap() ;

// Min-heap / priority queue operations:
   void insert( KeyType key ) ;
   KeyType minimum( ) ;
   KeyType extractMin( ) ;
   void decreaseKey( int i, KeyType key ) ;

// Auxiliary operations:
   inline bool empty() { return heapSize == 0 ; } // tests for empty heap
   void ShowHeap( int i, int depth ) ;  // Shows heap structure
   void PrintHeap( ) ;                  // Print heap in array order
   int search( KeyType key ) ;          // Useful for debugging
   void minHeapSort(int n) ;  
} ;

#endif
