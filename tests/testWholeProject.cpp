// This encodes and decodes all the textfiles and sees if they match
#include "../src/Decoder.h"
#include "../src/Encoder.h"
#include <fstream>
#include <iostream>
#include <string>

int encodeFile(int fileNum);
int testEncodingFiles();
int decodeFile(int fileNum);
bool codeMatchesExpected(int fileNum);
int testDecodingFiles();

const int FILES_TO_TEST = 12;

int main() {
  int exitCode = testEncodingFiles();
  if (exitCode == -1) {
    std::cout << "❌ Encoding failed!" << std::endl;
    return exitCode;
  }

  exitCode = testDecodingFiles();
  if (exitCode == -1) {
    std::cout << "❌ Encoding failed!" << std::endl;
  }
  std::cout << "✅ All files compressed + decompressed successfully!" << std::endl;
  return exitCode;
}

int encodeFile(int fileNum) {
  Encoder encoder;
  string pathToFile = "textFiles/txt" + to_string(fileNum) + ".txt";
  ifstream txtFile(pathToFile);
  if (!txtFile) {
    cerr << "Failed to open file " << fileNum << ". Exiting program" << endl;
    return -1;
  }

  // Now get chars from txt file and make the data structures we need to start compressing
  encoder.createCharCountDict(txtFile);
  encoder.createCharCountMinheap();
  if (encoder.getMinheapSize() == 0) {
    cout << "Empty file passed in. Cannot compress empty file, its already empty\n";
    return -1;
  }
  encoder.createHuffmanTreeFromMinheap();

  // After making data structures we can now get codes which we add to folder
  encoder.createCharCodeDict();
  ifstream txtFileCopy(pathToFile);
  filesystem::path dir = "textBinaries/" + to_string(fileNum);
  filesystem::create_directory(dir);
  ofstream serializedCode(dir / "serializedCode.txt");
  ofstream serializedHeap(dir / "serializedHeap.txt");
  if (!serializedCode || !serializedHeap) {
    cerr << "Serialized files couldn't be made" << endl;
    return -1;
  }

  // Serialize data
  encoder.serializeCodes(serializedCode, txtFileCopy);
  encoder.serializeHeap(serializedHeap);

  return 0;
}

int testEncodingFiles() {
  // You can test files 1-10
  unsigned fails = 0;
  for (unsigned fileNum = 1; fileNum <= FILES_TO_TEST; ++fileNum) {
    int exitCode = encodeFile(fileNum);
    if (exitCode == -1) {
      cout << "❌ Encoding on file " << fileNum << " failed!" << endl;
      fails++;
    }
  }

  if (fails > 0) {
    cout << FILES_TO_TEST - fails << " out of " << FILES_TO_TEST << " cases passed!\n";
    return -1;
  }
  cout << "✅ Congrats! All encodings passed!\n";
  return 0;
}

int decodeFile(int fileNum) {
  Decoder decoder;
  ifstream serializedHeap("textBinaries/" + to_string(fileNum) + "/serializedHeap.txt");
  ofstream decompressedTxtFile("textDecompressed/" + to_string(fileNum) +
                               "/decompressedTxtFile.txt");
  if (!serializedHeap.is_open()) {
    cout << "Failed to open compressed file, ensure the compressed folder is in this directory\n";
    return -1;
  }

  // Remake tree to translate binary codes, then use codes to traverse tree
  decoder.deserializeMinheap(serializedHeap);
  decoder.remakeDataStructures();
  ifstream binaryFile2("textBinaries/" + to_string(fileNum) + "/serializedCode.txt");
  decoder.traverseTreeAndAppendChars(binaryFile2, decompressedTxtFile);
  return 0;
}

bool codeMatchesExpected(int fileNum) {
  // Read from textBinaries/filenum and textDecompressed
  ifstream expectedTxtFile("textFiles/txt" + to_string(fileNum) + ".txt");
  ifstream createdTxtFile("textDecompressed/" + to_string(fileNum) + "/decompressedTxtFile.txt");
  if (!expectedTxtFile.is_open()) {
    std::cout << "Couldn't open created file!" << std::endl;
    return false;
  }
  string expectedLine;
  string createdLine;

  while (getline(expectedTxtFile, expectedLine)) {
    getline(createdTxtFile, createdLine);
    if (createdLine != expectedLine) {
      return false;
    }
  }

  return true;
}

int testDecodingFiles() {
  // You can test files 1-10
  unsigned fails = 0;
  for (unsigned fileNum = 1; fileNum <= FILES_TO_TEST; ++fileNum) {
    decodeFile(fileNum);
    if (!codeMatchesExpected(fileNum)) {
      cout << "❌ Decoding on file " << fileNum << " failed!" << endl;
      fails++;
    }
  }

  if (fails > 0) {
    cout << FILES_TO_TEST - fails << " out of " << FILES_TO_TEST << " cases passed!\n";
    return -1;
  }
  cout << "✅ Congrats! All decodings passed!\n";
  return 0;
}
