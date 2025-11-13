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
  int count;
  unique_ptr<CharCountNode> left;
  unique_ptr<CharCountNode> right;
  CharCountNode(string charr, int count) : charr(charr), count(count) {}
};

class Minheap {
public:
  vector<unique_ptr<CharCountNode>> m_charCountMinheap;

  void insert(string charr, int count);
  void insertNode(unique_ptr<CharCountNode>& node);
  void percolateUp(int index);
  unique_ptr<CharCountNode> pop();
  void percolateDown(int index);
  void printMinheap();
};

#endif
