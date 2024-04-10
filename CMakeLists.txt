cmake_minimum_required(VERSION 3.24)
project(temptemp)

set(CMAKE_CXX_STANDARD 17)

add_executable(temptemp main.cpp bitbuffer.h bitbuffer.cpp huffman.cpp huffman.h binheap.cpp binheap.h huffman-test.cpp)
