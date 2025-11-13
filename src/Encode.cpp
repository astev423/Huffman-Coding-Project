#include "Encode.h"

// First open a file
// dynamically allocate dictionary because it will take up a lot of space
// charsAndTheirOccurences = make_unique<unordered_map<string, int>>();

void Encoder::createCharCountDict(ifstream& txtFile) {
  char charr;

  if (txtFile.is_open()) {
    while (txtFile.get(charr)) {
      string key(1, charr);
      ++m_charsAndTheirOccurences[key];
      ++m_totalCharCount;
      // for debugging special chars
      // cout << charr << endl;
      // if (!isalnum(static_cast<unsigned char>(charr))) {
      // cout << "Special char: '" << charr << "' (ASCII " << static_cast<int>(charr) << ")\n";
      //}
    }
    txtFile.close();
  } else {
    cerr << "Error: Unable to open file.\n";
  }
}

// Insert all dictionary values to make minheap
void Encoder::createCharCountMinheap() {
  for (const auto& [charr, count] : m_charsAndTheirOccurences) {
    m_minheap.insert(charr, count);
  }
}

// Getters and setters
unordered_map<string, int>& Encoder::getCharDict() { return m_charsAndTheirOccurences; }
int Encoder::getTotalCharCount() { return m_totalCharCount; }
void Encoder::resetDict() { m_charsAndTheirOccurences.clear(); }
void Encoder::resetCharCount() { m_totalCharCount = 0; }
