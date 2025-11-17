#include "../../src/Encoder.h"

Encoder makeCodesFromFile();

int main() {
  ifstream txtFile("../textFiles/txt9.txt");
  Encoder encoder = makeCodesFromFile();
  // Need to another txtFile, for some reason can't reuse it
  // ifstream txtFile("./test.txt");
  encoder.makeCompressedFolder(txtFile);
  for (const auto& [key, value] : encoder.getCharCodes()) {
    std::cout << "Char: " << key << ", code: " << value << std::endl;
  }
  return 0;
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
