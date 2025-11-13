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

void HuffmanTree::postOrderTraversal(const unique_ptr<CharCountNode>& root) {
  if (root == nullptr) {
    return;
  }

  postOrderTraversal(root->left);
  postOrderTraversal(root->right);
  std::cout << root->charr << " count = " << root->count << std::endl;
}
