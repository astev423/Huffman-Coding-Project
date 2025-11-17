#ifndef DECODER_H
#define DECODER_H

#include "Encoder.h"

class Decoder {
private:
public:
  Encoder m_encoder;
  void deserializeMinheap(ifstream& binaryFile);
  void remakeDataStructures();
  void traverseTreeAndAppendChars(ifstream& binaryFile, ofstream& decompressedTxtFile);
  int decode();
  void printEachByteInBinary(ifstream& binaryFile);
};

#endif
