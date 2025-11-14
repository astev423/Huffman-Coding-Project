#include "Minheap.h"
#include <algorithm>
#include <memory>

void Minheap::insert(string charr, unsigned count) {
  m_charCountMinheap.push_back(make_unique<CharCountNode>(charr, count));
  percolateUp(m_charCountMinheap.size() - 1);
}

void Minheap::insertNode(unique_ptr<CharCountNode>& node) {
  // Push_back makes a copy, so we must use move to transfer ownership to vector
  m_charCountMinheap.push_back(std::move(node));
  percolateUp(m_charCountMinheap.size() - 1);
}

void Minheap::percolateUp(unsigned index) {
  while (index > 0) {
    unsigned parentIndex = (index - 1) / 2;
    if (m_charCountMinheap[index]->count < m_charCountMinheap[parentIndex]->count) {
      swap(m_charCountMinheap[index], m_charCountMinheap[parentIndex]);
      index = parentIndex;
    } else
      break;
  }
}

unique_ptr<CharCountNode> Minheap::pop() {
  if (m_charCountMinheap.size() == 0) {
    cerr << "ALERT ALERT, FATAL ERROR, TRYING TO POP FROM EMPTY HEAP" << endl;
    return nullptr;
  }

  // Since we are using unique ptrs to get access to the top I need to transfer ownership
  // After ownership is transfered top element in the vector will be null
  unique_ptr<CharCountNode> minCharNode = std::move(m_charCountMinheap[0]);
  // If size is one just shrink vector, no need to percolate
  if (m_charCountMinheap.size() == 1) {
    m_charCountMinheap.pop_back();
    return minCharNode;
  }

  // Now move the last element of the heap to the top
  m_charCountMinheap[0] = std::move(m_charCountMinheap.back());
  // Since it vector lost ownership last element is nullptr, we now remove it
  m_charCountMinheap.pop_back();
  percolateDown(0);

  return minCharNode;
}

void Minheap::percolateDown(unsigned index) {
  // Vector size is in size_t so we need to convert it to an unsigned to use in conditionals
  unsigned heapSize = static_cast<unsigned>(m_charCountMinheap.size());

  while (true) {
    unsigned leftIndex = 2 * index + 1;
    unsigned rightIndex = 2 * index + 2;
    unsigned smallestIndex = index;

    // Make sure we stay in bounds, swap if we find smaller child count
    if (leftIndex < heapSize &&
        m_charCountMinheap[leftIndex]->count < m_charCountMinheap[smallestIndex]->count) {
      smallestIndex = leftIndex;
    }
    if (rightIndex < heapSize &&
        m_charCountMinheap[rightIndex]->count < m_charCountMinheap[smallestIndex]->count) {
      smallestIndex = rightIndex;
    }
    // If no change happened that means heap properties sastified
    if (smallestIndex == index) {
      break;
    }

    swap(m_charCountMinheap[index], m_charCountMinheap[smallestIndex]);
    index = smallestIndex;
  }
}

void Minheap::printMinheap() {
  if (m_charCountMinheap.size() == 0) {
    cout << "Minheap is empty!!" << endl;
    return;
  }

  // Unique ptr not copiable but we can have references to it
  cout << "top is " << m_charCountMinheap[0]->charr << endl;
  for (const unique_ptr<CharCountNode>& node : m_charCountMinheap) {
    cout << "Char is " << node->charr << ", count is " << node->count << endl;
  }
}
