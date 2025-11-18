#include "HuffmanTree.h"
#include "Minheap.h"
#include <memory>
#include <vector>

// Order must be deterministic, so go off count, and then if equal, char order
bool HuffmanTree::node1Lesser(const unique_ptr<CharCountNode>& node1,
                              const unique_ptr<CharCountNode>& node2) {
  if (node1->count != node2->count) {
    return node1->count < node2->count;
  }
  return node1->charr < node2->charr;
}

void HuffmanTree::buildFromMinheap(const Minheap& minheap) {
  // Make copy so minheap doesn't get consumed, tricky because its unique ptr
  Minheap minheapCopy;
  vector<unique_ptr<CharCountNode>> heapCopy;
  heapCopy.reserve(minheap.m_charCountMinheap.size());
  for (const unique_ptr<CharCountNode>& node : minheap.m_charCountMinheap) {
    unique_ptr<CharCountNode> nodeCopy = make_unique<CharCountNode>(node->charr, node->count);
    heapCopy.push_back(std::move(nodeCopy));
  }
  minheapCopy.m_charCountMinheap = std::move(heapCopy);

  while (minheapCopy.m_charCountMinheap.size() > 1) {
    // Get the two nodes with lowest occurance rate
    unique_ptr<CharCountNode> firstCharNode = minheapCopy.pop();
    unique_ptr<CharCountNode> secondCharNode = minheapCopy.pop();

    if (!node1Lesser(firstCharNode, secondCharNode)) {
      swap(firstCharNode, secondCharNode);
    }
    string parentChar = "";
    if (firstCharNode->charr < secondCharNode->charr) {
      parentChar = firstCharNode->charr;
    } else {
      parentChar = secondCharNode->charr;
    }

    unique_ptr<CharCountNode> parentNode =
        make_unique<CharCountNode>(parentChar, firstCharNode->count + secondCharNode->count);
    // Parent will be new owners of the allocated memory
    parentNode->left = std::move(firstCharNode);
    parentNode->right = std::move(secondCharNode);
    minheapCopy.insertNode(parentNode);
  }

  // Always one node left, so pop that and make that our root
  root = minheapCopy.pop();
}

void HuffmanTree::createCharCodesViaDFS(const unique_ptr<CharCountNode>& root,
                                        unordered_map<string, string>& charsAndCodes,
                                        string curPath) {
  if (root == nullptr) {
    return;
  }

  if (root->charr == "\n") {
    std::cout << "*************RED ALERT********************" << std::endl;
  }
  charsAndCodes[root->charr] = curPath;
  string pathCopy = curPath;
  createCharCodesViaDFS(root->left, charsAndCodes, curPath.append("0"));
  createCharCodesViaDFS(root->right, charsAndCodes, pathCopy.append("1"));
}

void HuffmanTree::postOrderTraversal(unique_ptr<CharCountNode>& root, unsigned& charsVisited) {
  if (root == nullptr) {
    return;
  }

  if (root->left == nullptr && root->right == nullptr) {
    ++charsVisited;
    std::cout << root->charr << " count = " << root->count << std::endl;
  }

  postOrderTraversal(root->left, charsVisited);
  postOrderTraversal(root->right, charsVisited);
}
