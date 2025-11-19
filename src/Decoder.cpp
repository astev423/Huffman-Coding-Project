#include "Decoder.h"
#include "Minheap.h"
#include <bitset>
#include <iostream>
#include <memory>

void Decoder::deserializeMinheap(ifstream& binaryFile) {
  string line;
  string charr;
  unsigned long countStartIndex = 0;
  bool firstRun = true;

  // Get data to remake datastructures
  while (getline(binaryFile, line)) {
    // Get total size char size so we know how much to decode
    if (firstRun) {
      m_encoder.m_totalCharCount = stoull(line);
      firstRun = false;
      continue;
    }

    string count = "";
    // Get the char and find where the count begins
    if (line[1] == 'E') {
      charr = "NEWLINE";
      countStartIndex = 8;
    } else {
      charr = line[0];
      countStartIndex = 2;
    }
    while (countStartIndex < line.size()) {
      count += line[countStartIndex];
      countStartIndex++;
    }
    // Do annoying conversion, no string to unsigned
    unsigned long longUnsignedCount = stoul(count);
    unsigned unsignedCount = static_cast<unsigned>(longUnsignedCount);

    unique_ptr<CharCountNode> node = make_unique<CharCountNode>(charr, unsignedCount);
    m_encoder.m_minheap.m_charCountMinheap.push_back(std::move(node));
  }
}

void Decoder::remakeDataStructures() {
  m_encoder.createHuffmanTreeFromMinheap();
  m_encoder.createCharCodeDict();
}

void Decoder::traverseTreeAndAppendChars(ifstream& binaryFile, ofstream& decompressedTxtFile) {
  unsigned char byte = 0;
  string bitsStr = "";
  // .get gives pointer without transfering ownership, so tree doesn't get modified
  CharCountNode* curNode = m_encoder.m_huffmanTree.root.get();

  while (m_encoder.m_totalCharCount > 0) {
    // Refill string with next byte if if we remove all bits
    if (bitsStr == "") {
      // Read expects char pointer but bitset needs unsigned char, so do conversion
      binaryFile.read(reinterpret_cast<char*>(&byte), 1);
      bitsStr = bitset<8>(byte).to_string();
    }

    // Get and remove the most sigificant bit from byte
    char bit = bitsStr[0];
    bitsStr.erase(bitsStr.begin());

    // Use the bit to tell us whether to go left or right in tree
    if (bit == '0') {
      curNode = curNode->left.get();
    } else {
      curNode = curNode->right.get();
    }

    // If we reach leaf node then we reached a char, so append char to file and minus from count
    if (!curNode->left && !curNode->right) {
      if (curNode->charr == "NEWLINE") {
        decompressedTxtFile << '\n';
      } else {
        decompressedTxtFile << curNode->charr;
      }
      --m_encoder.m_totalCharCount;
      // Once we reach leaf node then traversal is complete, so go back to root for next traversal
      curNode = m_encoder.m_huffmanTree.root.get();
    }
  }
}

int Decoder::decode() {
  cout << "Decompression mode. Looking for compressed folder" << endl;
  // Get serialized heap and make file for decompressing binary into text
  Decoder decoder;
  ifstream serializedHeap("compressed/serializedHeap.txt");
  ofstream decompressedTxtFile("decompressedTxtFile.txt");
  if (!serializedHeap.is_open()) {
    cout << "Failed to open compressed file, ensure the compressed folder is in this directory\n";
    return -1;
  }

  // Remake tree to translate binary codes, then use codes to traverse tree
  decoder.deserializeMinheap(serializedHeap);
  decoder.remakeDataStructures();
  ifstream binaryFile2("compressed/serializedCode.txt");
  decoder.traverseTreeAndAppendChars(binaryFile2, decompressedTxtFile);

  std::cout << "Decompression complete! Your decompressed data is in decompressedTxtFile.txt"
            << std::endl;
  return 0;
}

void Decoder::printEachByteInBinary(ifstream& binaryFile) {
  unsigned char byte = 0;
  int i = 0;
  std::cout << m_encoder.m_totalCharCount << std::endl;

  while (binaryFile.read(reinterpret_cast<char*>(&byte), 1)) {
    string byteStr = bitset<8>(byte).to_string();
    std::cout << byteStr;
    // Spacing between bytes, newline every 8 bytes
    if (i % 8 == 0) {
      std::cout << std::endl;
    } else {
      std::cout << ' ' << std::endl;
    }
  }
  std::cout << std::endl;
}
