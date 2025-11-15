#ifndef ENCODE_H
#define ENCODE_H

#include "HuffmanTree.h"
#include "Minheap.h"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <unordered_map>

class Encoder {
private:
  unsigned m_totalCharCount;
  HuffmanTree m_huffmanTree;
  Minheap m_minheap;

public:
  unordered_map<string, unsigned> m_charsAndTheirOccurences;
  unordered_map<string, string> m_charsAndCodes;
  Encoder() : m_totalCharCount(0) {}
  void createCharCountDict(ifstream& txtFile);
  void createCharCountMinheap();
  void createHuffmanTreeFromMinheap();
  void createCharCodeDict();
  void makeCompressedFolder(ifstream& txtFile);
  char convertStrToByte(string str);
  void serializeCodes(ostream& serializedCode, ifstream& txtFile);
  void serializeHeap(ostream& serializedCode);

  // Getters and setters
  unordered_map<string, unsigned>& getCharDict();
  unordered_map<string, string> getCharCodes();
  unsigned getMinheapSize();
  unsigned getTotalCharCount();
  void resetDict();
  void resetCharCount();
};
#endif
