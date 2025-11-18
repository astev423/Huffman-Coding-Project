#include "../../src/Decoder.h"
#include <memory>
#include <string>
#include <unordered_map>

int convertBinariesToTxt();
void convertBinaryToTxt(string pathToFolder);
// bool txtMatchesExpected(int fileNum);

int main() {
  int exitCode = convertBinariesToTxt();

  return exitCode;
}

int convertBinariesToTxt() {
  int fails = 0;
  int filesToTest = 6;
  for (int fileNum = 6; fileNum <= filesToTest; ++fileNum) {
    std::cout << "Testing file " << fileNum << std::endl;
    string pathToFolder = "binaries/" + to_string(fileNum);
    convertBinaryToTxt(pathToFolder);
    // if (!txtMatchesExpected(fileNum)) {
    ++fails;
    //}
    std::cout << std::endl;
  }

  if (fails == 0) {
    std::cout << "✅ Congratulations! All test cases passed" << std::endl;
    return 0;
  }
  return -1;
}

void convertBinaryToTxt(string pathToFolder) {
  Decoder decoder;

  ifstream serializedHeap(pathToFolder + "/serializedHeap.txt");
  ofstream decompressedTxtFile("decompressedTxtFiles/decompressedTxtFile.txt");
  if (!serializedHeap.is_open()) {
    cout << "Failed to open compressed file, ensure the compressed folder is in this directory/n";
    return;
  }

  // Remake tree to translate binary codes, then use codes to traverse tree
  decoder.deserializeMinheap(serializedHeap);
  vector<unique_ptr<CharCountNode>>& heap = decoder.m_encoder.m_minheap.m_charCountMinheap;
  std::cout << "Printing heap" << std::endl;
  for (const auto& node : heap) {
    std::cout << node->charr << " " << node->count << std::endl;
  }
  decoder.remakeDataStructures();
  unordered_map<string, string> codes = decoder.m_encoder.m_charsAndCodes;
  std::cout << "Printing codes" << std::endl;
  for (const auto& [charr, code] : codes) {
    std::cout << charr << " " << code << std::endl;
  }
  ifstream binaryFile2(pathToFolder + "/serializedCode.txt");
  decoder.traverseTreeAndAppendChars(binaryFile2, decompressedTxtFile);

  std::cout << "Decompression complete! Your decompressed data is in decompressedTxtFile.txt"
            << std::endl;
}
