#include "Encoder.h"
#include "HuffmanTree.h"
#include "Minheap.h"
#include <iomanip>

void Encoder::createCharCountDict(ifstream& txtFile) {
  char charr;

  while (txtFile.get(charr)) {
    string key(1, charr);
    ++m_charsAndTheirOccurences[key];
    ++m_totalCharCount;
  }
  txtFile.close();
}

// Insert all dictionary values to make minheap
void Encoder::createCharCountMinheap() {
  for (const auto& [charr, count] : m_charsAndTheirOccurences) {
    m_minheap.insert(charr, count);
  }
}

void Encoder::createHuffmanTreeFromMinheap() { m_huffmanTree.buildFromMinheap(m_minheap); }

void Encoder::createCharCodeDict() {
  m_huffmanTree.createCharCodesViaDFS(m_huffmanTree.root, m_charsAndCodes, "");
}

// Build integer matching string which allows us to cast to to char which represents a byte
unsigned char Encoder::convertStrToByte(string str) {
  int intByte = 0;
  for (char c : str) {
    if (c == '1')
      intByte = (intByte << 1) | 1;
    else
      intByte = (intByte << 1) | 0;
  }

  return static_cast<unsigned char>(intByte);
}

void Encoder::serializeCodes(ostream& serializedCode, ifstream& txtFile) {
  if (!txtFile.is_open()) {
    std::cout << "txtfile couldn't open in serializeCodes" << std::endl;
    return;
  }

  // Cpp file library stuff for getting size of file. Seekg moves read spot, tellg reports spot
  txtFile.seekg(0, std::ios::end);
  auto end1 = txtFile.tellg();
  std::cout << setprecision(3) << "File size originally: " << static_cast<float>(end1) / 1000
            << " KB\n";
  txtFile.seekg(0, std::ios::beg);

  // Loop that gets each char from file, finds its code, and appends that to new file
  string strByte = "";
  char charr;
  while (txtFile.get(charr)) {
    string key(1, charr);
    string codeStr = m_charsAndCodes[key];
    for (char bit : codeStr) {
      strByte += bit;
      if (strByte.size() == 8) {
        // Unsigned char reccomended for safely working with bits
        unsigned char newByte = convertStrToByte(strByte);
        // But put expects normal char so cast it back to normal char
        serializedCode.put(static_cast<char>(newByte));
        strByte = "";
      }
    }
  }

  // Add padding to make byte full 8 bits
  while (strByte.size() != 8) {
    strByte += "0";
  }
  unsigned char byteChar = convertStrToByte(strByte);
  serializedCode.put(static_cast<char>(byteChar));

  // Cpp file library stuff for getting size of file
  auto end2 = serializedCode.tellp();
  std::cout << setprecision(3) << "File compressed down to " << static_cast<float>(end2) / 1000
            << " KB\n";
}

void Encoder::serializeHeap(ostream& serializedHeap) {
  // Write size of heap so we know how much to decode
  serializedHeap << m_totalCharCount << '\n';
  // Since heap is unique_ptr we can't serialize it directly but we can easily rebuild it from this
  for (auto [charr, count] : m_charsAndTheirOccurences) {
    if (charr == "\n") {
      serializedHeap << "NEWLINE" << ' ' << count << '\n';
    } else {
      serializedHeap << charr << ' ' << count << '\n';
    }
  }
}

void Encoder::makeCompressedFolder(ifstream& txtFile) {
  // Make new folder and files
  filesystem::path dir = "compressed";
  filesystem::create_directory(dir);
  ofstream serializedCode(dir / "serializedCode.txt");
  ofstream serializedHeap(dir / "serializedHeap.txt");
  if (!serializedCode || !serializedHeap) {
    cerr << "Serialized files couldn't be made" << endl;
    return;
  }

  // Serialize data
  serializeCodes(serializedCode, txtFile);
  serializeHeap(serializedHeap);
}

// Getters and setters
unordered_map<string, unsigned>& Encoder::getCharDict() { return m_charsAndTheirOccurences; }
unordered_map<string, string> Encoder::getCharCodes() { return m_charsAndCodes; };
unsigned Encoder::getTotalCharCount() { return m_totalCharCount; }
unsigned Encoder::getMinheapSize() { return m_minheap.m_charCountMinheap.size(); }
void Encoder::resetDict() { m_charsAndTheirOccurences.clear(); }
void Encoder::resetCharCount() { m_totalCharCount = 0; }
