#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Minheap.h"

class HuffmanTree {
public:
  unique_ptr<CharCountNode> root;
  // make tree out of nodes then test dfs
  void buildFromMinheap(Minheap& minheap);
  void postOrderTraversal(const unique_ptr<CharCountNode>& root, int& leavesVisited,
                          int& charsVisited);
};

#endif
