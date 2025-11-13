#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Minheap.h"
#include <algorithm>
#include <memory>

class HuffmanTree {
public:
  unique_ptr<CharCountNode> root;
  // make tree out of nodes then test dfs
  void dfs();
  void buildFromMinheap(Minheap minheap);
};

#endif
