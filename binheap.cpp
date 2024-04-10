
// binheap.cpp implementation file for binary heaps

#include "binheap.h"
#include <iostream>
#include <iomanip>


// Utility routines used to implement binary heaps and heapSort

int parent ( int i ) { return i/2 ; }

int left ( int i ) { return 2*i ; }

int right ( int i ) { return 2*i + 1 ; }

void BinHeap :: minHeapify ( int i )
{
   int l, r, smallestloc ;
   KeyType temp ;

   l = left( i ) ;
   r = right( i ) ;

   if (l <= heapSize && *A[l] < *A[i ]){
       smallestloc = l;
   }else{
       smallestloc = i;
   }

   if (r <= heapSize && *A[r] < *A[smallestloc]){
       smallestloc = r;
   }

   if (i != smallestloc){
       std::swap(A[smallestloc], A[i]);
       minHeapify(smallestloc);
   }


   // You write the rest of this - remember this is a _min_ heap
}

void BinHeap :: buildMinHeap( int n )
{
    heapSize = n;

    for(int i =heapSize/2; i > 0; --i){
        minHeapify(i);
    }

}


// Constructors, Destructor
BinHeap :: BinHeap() { 
  heapSize = 0 ; length = 1000 ; A = new KeyType[1001] ; 
}
BinHeap :: BinHeap( int arrayLength ) {
   heapSize = 0 ; length = arrayLength ; A = new KeyType[arrayLength+1] ;
}
BinHeap :: ~BinHeap() { delete[] A ; }


// Min-heap, min priority queue operations

void BinHeap :: insert( KeyType key )
{
   heapSize++ ;
   A[heapSize] = key ;  
   decreaseKey( heapSize, key ) ;
}

KeyType BinHeap :: minimum( )
{
   return A[1] ;    // Assumes heap is not empty! 
}

KeyType BinHeap :: extractMin( )
{
   KeyType min ;

   if ( heapSize < 1 ) {
      cout << "\nHeap underflow in extractMin()\n\n" ; return 0 ;
   }
   
   min = A[1] ;

   A[1] = A[heapSize];
   heapSize -= 1;
   minHeapify(1);

   return min ;
}

void BinHeap :: decreaseKey( int i, KeyType key )
{
   KeyType temp ;

   if ( key->freq > A[i]->freq ) {
      cout << "\nKey larger than A[i] in decreaseKey()\n\n" ; return ;
   }

   A[i] = key;

   buildMinHeap(heapSize);
}


// Auxiliary operations

// Shows the structure of the binary heap
void BinHeap :: ShowHeap( int i, int depth )
{
   if ( i <= heapSize ) {
      ShowHeap( right(i), depth+1 ) ;
      cout << setw( depth*6 +4 ) << A[i]->freq << endl ;
      ShowHeap( left(i), depth+1 ) ;
   }
}

// Just prints A[] as a horizontal array
void BinHeap :: PrintHeap()
{
   cout << "Heap elements in the array:\n" ;
   for ( int i = 1 ; i <= heapSize ; i++ )
      cout << A[i]->freq << " " ;
   cout << endl ;
}

// A routine that is useful for testing decreaseKey()
int BinHeap :: search( KeyType key )
{
   for ( int i = 1 ; i <= heapSize ; i++ )
      if ( A[i]->freq == key->freq ) return i ;
   return 0 ;
}


void BinHeap :: minHeapSort( int n )
{
    int size = heapSize;

    buildMinHeap(n);
    for(int i = heapSize; i >= 2; --i){
        std::swap(A[1], A[i]);
        heapSize -= 1;
        minHeapify(1);
    }
    heapSize = size;
}
