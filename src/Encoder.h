#ifndef ENCODER_H
#define ENCODER_H

#include "HuffmanTree.h"
#include "Minheap.h"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <unordered_map>

class Encoder {
private:
  Minheap m_minheap;

public:
  HuffmanTree m_huffmanTree;
  unsigned long long m_totalCharCount;
  unordered_map<string, unsigned> m_charsAndTheirOccurences;
  unordered_map<string, string> m_charsAndCodes;
  Encoder() : m_totalCharCount(0) {}
  void createCharCountDict(ifstream& txtFile);
  void createCharCountMinheap();
  void createHuffmanTreeFromMinheap();
  void createCharCodeDict();
  void makeCompressedFolder(ifstream& txtFile);
  unsigned char convertStrToByte(string str);
  void serializeCodes(ostream& serializedCode, ifstream& txtFile);
  void serializeHeap(ostream& serializedCode);
  int encode();

  // Getters and setters
  unordered_map<string, unsigned>& getCharDict();
  unordered_map<string, string> getCharCodes();
  unsigned getMinheapSize();
  unsigned getTotalCharCount();
  void resetDict();
  void resetCharCount();
};
#endif
