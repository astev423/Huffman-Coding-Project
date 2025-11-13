// To run this copy and paste this into terminal
/*
g++ -std=c++23 -Wall -Werror  testHuffmanTree.cpp ../../src/HuffmanTree.cpp ../../src/Minheap.cpp &&
./a.out
*/

#include "../../src/HuffmanTree.h"
#include <iostream>
#include <memory>

Minheap makeMinheap();
void buildHuffmanTree(HuffmanTree& huffmanTree);

int main() {
  HuffmanTree huffmanTree;
  buildHuffmanTree(huffmanTree);
  std::cout << "now running postorder dfs!!!!!" << std::endl;
  huffmanTree.postOrderTraversal(huffmanTree.root);

  std::cout << std::endl;
  std::cout << "making new tree" << std::endl;
  HuffmanTree newHuffmanTree;
  Minheap minheap = makeMinheap();
  newHuffmanTree.buildFromMinheap(minheap);
  std::cout << "now running postorder dfs!!!!!" << std::endl;
  newHuffmanTree.postOrderTraversal(newHuffmanTree.root);

  return 0;
}

// Just for testing very basics of tree
void buildHuffmanTree(HuffmanTree& huffmanTree) {
  unique_ptr<CharCountNode> root = make_unique<CharCountNode>("INTERNAL", 5);
  unique_ptr<CharCountNode> child1 = make_unique<CharCountNode>("b", 2);
  unique_ptr<CharCountNode> child2 = make_unique<CharCountNode>("c", 3);
  root->left = std::move(child1);
  root->right = std::move(child2);

  huffmanTree.root = std::move(root);
}

Minheap makeMinheap() {
  Minheap minheap;
  vector<string> expectedChars = {"j", "1", "e", "g", "d", "c", "f", "b", "h", "i", "a"};
  minheap.insert("a", 4);
  minheap.insert("b", 6);
  minheap.insert("c", 5);
  minheap.insert("1", 1);
  minheap.insert("d", 2);
  minheap.insert("e", 3);
  minheap.insert("f", 4);
  minheap.insert("g", 4);
  minheap.insert("h", 10);
  minheap.insert("i", 40);
  minheap.insert("j", 0);

  return minheap;
}
