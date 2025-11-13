// To run this copy and paste this into terminal
/*
g++ -std=c++23 -Wall -Werror  testHuffmanTree.cpp ../../src/HuffmanTree.h ../../src/Minheap.cpp &&
./a.out
*/

#include "../../src/HuffmanTree.h"
#include <iostream>
#include <memory>

void buildHuffmanTree(HuffmanTree& huffmanTree);

int main() {
  HuffmanTree huffmanTree;
  buildHuffmanTree(huffmanTree);
  return 0;
}

void buildHuffmanTree(HuffmanTree& huffmanTree) {
  unique_ptr node = make_unique<CharCountNode>("b", 4);
  cout << node->charr << endl;
  node->left = make_unique<CharCountNode>("c", 4);
  cout << node->left->charr << endl;
  if (node->left == nullptr) {
    cout << "have null child left" << endl;
  }
  if (node->right == nullptr) {
    cout << "have null child right" << endl;
  }
  huffmanTree.root = std::move(node);
  std::cout << "huffman tree root char is " << huffmanTree.root->charr << std::endl;
}
