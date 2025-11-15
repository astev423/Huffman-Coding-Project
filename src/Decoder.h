#ifndef DECODER_H
#define DECODER_H

#include "Encode.h"

class Decoder {
private:
public:
  Encoder m_encoder;
  void deserializeMinheap(ifstream& binaryFile);
  // int findTotalCharCountOfFile(ifstream& binaryFile);
  // void traverseTreeAndAppendChars(ifstream& binaryFile, ofstream& decompressedTxtFile);
};

#endif
