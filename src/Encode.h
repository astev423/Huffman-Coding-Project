#ifndef ENCODE_H
#define ENCODE_H

#include "Minheap.h"
#include <cctype>
#include <fstream>
#include <unordered_map>

class Encoder {
private:
  // This doesn't have to be allocated as it just holds ascii unique chars and ints for them
  unordered_map<string, int> m_charsAndTheirOccurences;
  int m_totalCharCount;
  unordered_map<string, string> m_charsAndTheirCodes;
  // HuffmanTree m_huffmanTree;

public:
  Minheap m_minheap;
  Encoder() : m_totalCharCount(0) {}
  void createCharCountDict(ifstream& txtFile);
  void createCharCountMinheap();
  /*
  void createHuffmanTreeFromMinheap();
  void mapCharsToTreeCodes();
  void turnCodesIntoBinaryFile();
  void createAndInsertIntoCompressedFolder();
   */
  // Getters and setters
  unordered_map<string, int>& getCharDict();
  int getTotalCharCount();
  void resetDict();
  void resetCharCount();
};
#endif
