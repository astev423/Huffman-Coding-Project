#include "Encoder.h"
#include "HuffmanTree.h"
#include "Minheap.h"
#include <iomanip>
#include <iostream>
#include <memory>

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
    if (charr == "\n") {
      std::cout << "********inserting newline into heap" << std::endl;
      m_minheap.insert("NEWLINE", count);
    } else {
      m_minheap.insert(charr, count);
    }
  }
  std::cout << "Printing out minheap" << std::endl;
  for (const auto& node : m_minheap.m_charCountMinheap) {
    std::cout << node->charr << " " << node->count << std::endl;
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
    if (charr == '\n') {
      key = "NEWLINE";
    }
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
  std::cout << "Printing out serialized minheap" << std::endl;
  for (const auto& node : m_minheap.m_charCountMinheap) {
    if (node->charr == "\n") {
      std::cout << "NEWLINE" << " " << node->count << std::endl;
    } else {
      std::cout << node->charr << " " << node->count << std::endl;
    }
  }
  serializedHeap << m_totalCharCount << '\n';
  for (const unique_ptr<CharCountNode>& node : m_minheap.m_charCountMinheap) {
    if (node->charr == "\n") {
      serializedHeap << "NEWLINE" << ' ' << node->count << '\n';
    } else {
      serializedHeap << node->charr << ' ' << node->count << '\n';
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

int Encoder::encode() {
  cout << "Compression mode: Carefully type the full name of your file (including the .txt)\n";
  string fileName = "";
  cin >> fileName;
  ifstream txtFile(fileName);
  if (!txtFile.is_open()) {
    cout << "Failed to open text file, make sure its spelled correctly (case sensitive)\n";
    return -1;
  }

  // Now get chars from txt file and make the data structures we need to start compressing
  createCharCountDict(txtFile);
  createCharCountMinheap();
  if (getMinheapSize() == 0) {
    cout << "Empty file passed in. Cannot compress empty file, its already empty\n";
    return -1;
  }
  createHuffmanTreeFromMinheap();

  // After making data structures we can now get codes which we add to folder
  createCharCodeDict();
  ifstream txtFileCopy(fileName);
  makeCompressedFolder(txtFileCopy);

  cout << "Compression complete! Your file 'compressed.txt' is in the folder 'compressed'\n";
  return 0;
}

// Getters and setters
unordered_map<string, unsigned>& Encoder::getCharDict() { return m_charsAndTheirOccurences; }
unordered_map<string, string> Encoder::getCharCodes() { return m_charsAndCodes; };
unsigned Encoder::getTotalCharCount() { return m_totalCharCount; }
unsigned Encoder::getMinheapSize() { return m_minheap.m_charCountMinheap.size(); }
void Encoder::resetDict() { m_charsAndTheirOccurences.clear(); }
void Encoder::resetCharCount() { m_totalCharCount = 0; }
