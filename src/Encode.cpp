#include "Encode.h"

// First open a file
// dynamically allocate dictionary because it will take up a lot of space
// charsAndTheirOccurences = make_unique<unordered_map<string, int>>();

void Encoder::createCharCountDict(ifstream &txtFile) {
  char charr;

  if (txtFile.is_open()) {
    while (txtFile.get(charr)) {
      string key(1, charr);
      ++charsAndTheirOccurences[key];
      ++totalCharCount;
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

unordered_map<string, int> &Encoder::getCharDict() { return charsAndTheirOccurences; }

int Encoder::getTotalCharCount() { return totalCharCount; }

void Encoder::resetDict() { charsAndTheirOccurences.clear(); }
void Encoder::resetCharCount() { totalCharCount = 0; }
