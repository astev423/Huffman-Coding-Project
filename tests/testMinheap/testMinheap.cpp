// To run this copy and paste this into terminal
/*
g++ -std=c++23 -Wall -Werror  testMinheap.cpp ../../src/Minheap.cpp && ./a.out
*/

#include "../../src/Minheap.h"
#include <memory>

void testInsertion();
void testPopping();

int main() {
  testInsertion();
  cout << endl;
  testPopping();

  return 0;
}

// Since we are using unique ptrs we need to pass by reference bc copies cant be made
// Passing by reference allows function to directly use parameter so it works
void testInsertion() {
  cout << "Testing insertion..." << endl;
  unique_ptr<Minheap> minheap = make_unique<Minheap>();
  vector<string> expectedChars = {"j", "1", "e", "g", "d", "c", "f", "b", "h", "i", "a"};
  minheap->insert("a", 4);
  minheap->insert("b", 6);
  minheap->insert("c", 5);
  minheap->insert("1", 1);
  minheap->insert("d", 2);
  minheap->insert("e", 3);
  minheap->insert("f", 4);
  minheap->insert("g", 4);
  minheap->insert("h", 10);
  minheap->insert("i", 40);
  minheap->insert("j", 0);
  for (size_t index = 0; index < minheap->m_charCountMinheap.size(); ++index) {
    const unique_ptr<CharCountNode>& node = minheap->m_charCountMinheap[index];
    if (node->charr != expectedChars[index]) {
      cerr << "❌ Char is " << node->charr << ", but expected " << expectedChars[index] << endl;
      cerr << "❌ Test on insertion failed!" << endl;
      return;
    }
  }
  cout << "✅ Test on insertion succeeded!" << endl;
}

void testPopping() {
  cout << "Testing popping..." << endl;
  unique_ptr<Minheap> minheap = make_unique<Minheap>();
  vector<string> expectedTopChars = {"e", "d", "a", "c", "b", "f"};
  minheap->insert("a", 444);
  minheap->insert("b", 4903248);
  minheap->insert("c", 90999);
  minheap->insert("d", 9);
  minheap->insert("e", 0);
  minheap->insert("f", 4903249);
  unique_ptr<CharCountNode> top;
  int index = 0;
  while (minheap->m_charCountMinheap.size() > 0) {
    top = minheap->pop();
    if (top->charr != expectedTopChars[index]) {
      cerr << "❌ Char " << top->charr << " is on top, but expected " << expectedTopChars[index]
           << endl;
      cerr << "❌ Test on insertion failed!" << endl;
      return;
    }
    ++index;
  }
  cout << "✅ Test on popping succeeded!" << endl;
}
