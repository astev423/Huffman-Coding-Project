#ifndef ENCODE_H
#define ENCODE_H

#include "Minheap.h"
#include <cctype>
#include <fstream>
#include <unordered_map>

class Encoder {
private:
  // This doesn't have to be allocated as it just holds ascii unique chars and ints for them
  unordered_map<string, int> charsAndTheirOccurences;
  int totalCharCount;
  unordered_map<string, string> charsAndTheirCodes;
  vector<CharCountNode> charCountMinheap;
  // HuffmanTree huffmanTree;

public:
  Encoder() : totalCharCount(0) {}
  void createCharCountDict(ifstream& txtFile);
  unordered_map<string, int>& getCharDict();
  int getTotalCharCount();
  void resetDict();
  void resetCharCount();
  void createCharCountMinheap();
  /*
  void createHuffmanTreeFromMinheap();
  void mapCharsToTreeCodes();
  void turnCodesIntoBinaryFile();
  void createAndInsertIntoCompressedFolder();
   */
};
#endif
