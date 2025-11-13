#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Minheap.h"
#include <memory>
#include <unordered_map>

class HuffmanTree {
public:
  unique_ptr<CharCountNode> root;
  // make tree out of nodes then test dfs
  void buildFromMinheap(Minheap& minheap);
  void postOrderTraversal(const unique_ptr<CharCountNode>& root, int& leavesVisited,
                          int& charsVisited);
  void getCharCodesDFS(const unique_ptr<CharCountNode>& root,
                       unordered_map<string, string>& charsAndCodes, string curPath);
};

#endif
