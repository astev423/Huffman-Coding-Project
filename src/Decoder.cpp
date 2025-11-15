#include "Decoder.h"

void Decoder::deserializeMinheap(ifstream& binaryFile) {
  string line;
  string charr;
  string count;

  // Get data to remake datastructures
  while (getline(binaryFile, line)) {
    istringstream iss(line);
    iss >> charr >> count;
    // Do annoying conversion, no string to unsigned
    unsigned long longUnsignedCount = stoul(count);
    unsigned unsignedCount = static_cast<unsigned>(longUnsignedCount);

    m_encoder.m_charsAndTheirOccurences[charr] = unsignedCount;
  }

  // Remake datastructures
  m_encoder.createCharCountMinheap();
  m_encoder.createHuffmanTreeFromMinheap();
  m_encoder.createCharCodeDict();

  for (const auto& [k, v] : m_encoder.m_charsAndCodes)
    std::cout << k << ": " << v << '\n';
}
