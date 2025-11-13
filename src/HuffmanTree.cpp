#include "HuffmanTree.h"
#include "Minheap.h"
#include <memory>

void HuffmanTree::buildFromMinheap(Minheap& minheap) {
  while (minheap.m_charCountMinheap.size() > 1) {
    // Get the two nodes with lowest occurance rate
    unique_ptr<CharCountNode> firstCharNode = minheap.pop();
    unique_ptr<CharCountNode> secondCharNode = minheap.pop();

    unique_ptr<CharCountNode> parentNode =
        make_unique<CharCountNode>("INTERNAL", firstCharNode->count + secondCharNode->count);
    // Parent will be new owners of the allocated memory
    parentNode->left = std::move(firstCharNode);
    parentNode->right = std::move(secondCharNode);
    minheap.insertNode(parentNode);
  }

  // Always one node left, so pop that and make that our root
  root = minheap.pop();
}

void HuffmanTree::getCharCodesDFS(const unique_ptr<CharCountNode>& root,
                                  unordered_map<string, string>& charsAndCodes, string curPath) {
  if (root == nullptr) {
    return;
  }

  if (root->charr != "INTERNAL") {
    charsAndCodes[root->charr] = curPath;
  }
  string pathCopy = curPath;
  getCharCodesDFS(root->left, charsAndCodes, curPath.append("0"));
  getCharCodesDFS(root->right, charsAndCodes, pathCopy.append("1"));
}

void HuffmanTree::postOrderTraversal(const unique_ptr<CharCountNode>& root, int& leavesVisited,
                                     int& charsVisited) {
  if (root == nullptr) {
    return;
  }

  if (root->charr != "INTERNAL") {
    ++charsVisited;
  }
  if (root->left == nullptr && root->right == nullptr) {
    ++leavesVisited;
  }

  postOrderTraversal(root->left, leavesVisited, charsVisited);
  postOrderTraversal(root->right, leavesVisited, charsVisited);
  std::cout << root->charr << " count = " << root->count << std::endl;
}
