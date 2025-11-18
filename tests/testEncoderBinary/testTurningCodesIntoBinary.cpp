#include "../../src/Encoder.h"
#include <bitset>

Encoder makeCodesFromFile();
int makeBinaryFiles();
void makeBinaryFile(string pathToFile);
bool createdBinaryMatchesExpectedBinary(int fileNum);
void printCodesForCurFileChars(const Encoder& encoder);

int main() {
  int exitCode = makeBinaryFiles();
  // int exitCode = 0;
  // makeBinaryFile("../textFiles/txt5.txt");
  return exitCode;
}

int makeBinaryFiles() {
  int fails = 0;
  int filesToTest = 6;
  for (int fileNum = 5; fileNum <= filesToTest; ++fileNum) {
    std::cout << "Testing file " << fileNum << std::endl;
    string pathToFile = "../textFiles/txt" + to_string(fileNum) + ".txt";
    makeBinaryFile(pathToFile);
    if (!createdBinaryMatchesExpectedBinary(fileNum)) {
      ++fails;
    }
    std::cout << std::endl;
  }

  if (fails == 0) {
    std::cout << "✅ Congratulations! All test cases passed" << std::endl;
    return 0;
  }
  return 1;
}

void makeBinaryFile(string pathToFile) {
  Encoder encoder;
  ifstream txtFile(pathToFile);
  if (!txtFile) {
    cerr << "Failed to open file " << pathToFile << ". Exiting makeBinaryFile" << endl;
    return;
  }

  encoder.createCharCountDict(txtFile);
  encoder.createCharCountMinheap();
  if (encoder.getMinheapSize() == 0) {
    cout << "Empty file passed in. Cannot compress empty file, its already empty\n";
    return;
  }
  encoder.createHuffmanTreeFromMinheap();

  // After making data structures we can now get codes which we add to folder
  encoder.createCharCodeDict();
  ifstream txtFileCopy(pathToFile);
  encoder.makeCompressedFolder(txtFileCopy);
  printCodesForCurFileChars(encoder);
}

bool createdBinaryMatchesExpectedBinary(int fileNum) {
  // Read binary of both expected and manufactured
  string expectedBinaryPath = "expectedBinaries/" + to_string(fileNum) + ".txt";
  ifstream expectedBinary(expectedBinaryPath);
  ifstream createdBinary("compressed/serializedCode.txt");
  if (!expectedBinary.is_open() || !createdBinary.is_open()) {
    std::cout << "Failed to open files at" << fileNum << std::endl;
    return false;
  }

  unsigned char byte1 = 0;
  unsigned char byte2 = 0;

  while (expectedBinary.read(reinterpret_cast<char*>(&byte1), 1)) {
    createdBinary.read(reinterpret_cast<char*>(&byte2), 1);
    string byteStr1 = bitset<8>(byte1).to_string();
    string byteStr2 = bitset<8>(byte2).to_string();
    if (byteStr1 != byteStr2) {
      std::cout << "❌ Text file " << fileNum << " does not match expected binary" << std::endl;
      return false;
    }
  }

  std::cout << "✅ Text file " << fileNum << " matches expected binary" << std::endl;
  return true;
}

Encoder makeCodesFromFile() {
  // cin >> filename;
  Encoder encoder;
  ifstream txtFile("../textFiles/txt9.txt");
  // ifstream txtFile("./test.txt");
  if (!txtFile.is_open()) {
    cout << "Failed to open text file, make sure its spelled correctly (case sensitive)\n";
  }

  // Now get chars from txt file and make the data structures we need to start compressing
  encoder.createCharCountDict(txtFile);
  encoder.createCharCountMinheap();
  if (encoder.getMinheapSize() == 0) {
    cout << "Empty file passed in. Cannot compress empty file, its already empty\n";
  }
  encoder.createHuffmanTreeFromMinheap();

  // After making data structures we can now get codes and append them to binary of empty file
  encoder.createCharCodeDict();

  return encoder;
}

void printCodesForCurFileChars(const Encoder& encoder) {
  std::cout << "Printing codes for chars" << std::endl;
  for (const auto& [charr, code] : encoder.m_charsAndCodes) {
    if (charr == "\n") {
      std::cout << "NEWLINE" << ":" << code << std::endl;
    } else {
      std::cout << charr << ":" << code << std::endl;
    }
  }
}
