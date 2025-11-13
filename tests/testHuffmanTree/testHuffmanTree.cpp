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
  int tempNum1 = 0;
  int tempNum2 = 0;
  huffmanTree.postOrderTraversal(huffmanTree.root, tempNum1, tempNum2);

  std::cout << std::endl;
  std::cout << "making new tree" << std::endl;
  HuffmanTree newHuffmanTree;
  Minheap minheap = makeMinheap();
  int heapSize = minheap.m_charCountMinheap.size();
  newHuffmanTree.buildFromMinheap(minheap);
  std::cout << "now running postorder dfs!!!!!" << std::endl;
  int leavesInTreeVisited = 0;
  int charsInTreeVisited = 0;
  newHuffmanTree.postOrderTraversal(newHuffmanTree.root, leavesInTreeVisited, charsInTreeVisited);

  // Test if values are right
  std::cout << "This traversal visited " << leavesInTreeVisited << " leaves and "
            << charsInTreeVisited << " chars" << std::endl;
  if (heapSize == leavesInTreeVisited && heapSize == charsInTreeVisited) {
    cout << "✅ Nodes visited, leaf nodes, and heap size all match! Test passed!" << endl;
  } else {
    cout << "❌ Tests failed!!! Values not matching" << endl;
  }

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
