#include "../../src/HuffmanTree.h"
#include <iostream>
#include <memory>

Minheap makeMinheap();
void buildHuffmanTree(HuffmanTree& huffmanTree);
void simpleTreeTest();
void testNodesAndCodes();

int main() {
  simpleTreeTest();
  testNodesAndCodes();

  return 0;
}

// Just for testing very basics of tree
void simpleTreeTest() {
  HuffmanTree huffmanTree;
  buildHuffmanTree(huffmanTree);
  std::cout << "now running postorder dfs!!!!!" << std::endl;
  unsigned tempNum = 0;
  huffmanTree.postOrderTraversal(huffmanTree.root, tempNum);
}

// Builds a decently complex tree and prints out related info on it
void testNodesAndCodes() {
  std::cout << std::endl;
  std::cout << "making new tree" << std::endl;
  HuffmanTree newHuffmanTree;
  Minheap minheap = makeMinheap();
  unsigned heapSize = minheap.m_charCountMinheap.size();
  newHuffmanTree.buildFromMinheap(minheap);
  std::cout << "now running postorder dfs!!!!!" << std::endl;
  unsigned charsInTreeVisited = 0;
  newHuffmanTree.postOrderTraversal(newHuffmanTree.root, charsInTreeVisited);

  // Test if values are right
  std::cout << "This traversal visited " << charsInTreeVisited << " chars" << std::endl;
  if (heapSize == charsInTreeVisited) {
    cout << "✅ Nodes visited, leaf nodes, and heap size all match! Test passed!" << endl;
  } else {
    cout << "❌ Tests failed!!! Values not matching" << endl;
  }

  // Test codes now
  unordered_map<string, string> expectedCodes = {
      {"g", "1000010"}, {"(", "11"},         {"f", "1000001"},    {"h", "100010"},
      {"b", "1000110"}, {"a", "1000000"},    {"d", "100011111"},  {"c", "1000011"},
      {"?", "101"},     {"j", "1000111101"}, {"1", "1000111100"}, {"e", "10001110"},
      {"&", "0"},       {"i", "1001"}};

  unordered_map<string, string> charsAndCodes;
  string curPath = "";
  newHuffmanTree.createCharCodesViaDFS(newHuffmanTree.root, charsAndCodes, curPath);
  if (expectedCodes == charsAndCodes) {
    cout << "✅ Codes match expected codes!" << endl;
  } else {
    cout << "❌ Codes DON'T match expected codes" << endl;
  }
  // uncomment to check generated codes if something went wrong
  // for (const auto& [key, value] : charsAndCodes) {
  //  std::cout << "Char: " << key << ", code: " << value << std::endl;
  //}
}

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
  // Insert 11 chars
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
  minheap.insert("?", 400);
  minheap.insert("(", 800);
  minheap.insert("&", 900);
  minheap.insert("j", 1);

  return minheap;
}
