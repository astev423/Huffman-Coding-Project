#ifndef DECODER_H
#define DECODER_H

#include "Encode.h"

class Decoder {
private:
  unordered_map<string, int> m_charsAndTheirOccurences;
  int m_totalCharCount;
  unordered_map<string, string> m_charsAndCodes;
  Minheap m_minheap;
  HuffmanTree m_huffmanTree;

public:
};

#endif
