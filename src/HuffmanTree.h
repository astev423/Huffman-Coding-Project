#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Minheap.h"
#include <memory>
#include <unordered_map>

class HuffmanTree {
public:
  unique_ptr<CharCountNode> root;
  bool node1Lesser(const unique_ptr<CharCountNode>& node1, const unique_ptr<CharCountNode>& node2);
  void buildFromMinheap(Minheap& minheap);
  void postOrderTraversal(const unique_ptr<CharCountNode>& root, unsigned& leavesVisited,
                          unsigned& charsVisited);
  void createCharCodesViaDFS(const unique_ptr<CharCountNode>& root,
                             unordered_map<string, string>& charsAndCodes, string curPath);
};

#endif
