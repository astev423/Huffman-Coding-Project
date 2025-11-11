#ifndef MINHEAP_H
#define MINHEAP_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct CharCountNode {
  // Don't need children, heap index math on vector supplies that
  string charr;
  int count;
  CharCountNode(string charr, int count) : charr(charr), count(count) {}
};

class Minheap {
public:
  // Vector does not have to be heap allocated as it just stores pointers, not the objects
  vector<unique_ptr<CharCountNode>> charCountMinheap;
  void insert(string charr, int count);
  void percolateUp(int index);
  unique_ptr<CharCountNode> pop();
  void percolateDown(int index);
  void printMinheap();
};

#endif
