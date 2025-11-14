#ifndef MINHEAP_H
#define MINHEAP_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct CharCountNode {
  // Char stored as string type for edge cases like parent nodes
  string charr;
  unsigned count;
  // Unique ptrs default to nullptr when not defined
  unique_ptr<CharCountNode> left;
  unique_ptr<CharCountNode> right;
  CharCountNode(string charr, unsigned count) : charr(charr), count(count) {}
};

class Minheap {
public:
  vector<unique_ptr<CharCountNode>> m_charCountMinheap;

  void insert(string charr, unsigned count);
  void insertNode(unique_ptr<CharCountNode>& node);
  void percolateUp(unsigned index);
  unique_ptr<CharCountNode> pop();
  void percolateDown(unsigned index);
  void printMinheap();
};

#endif
