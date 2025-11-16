#include "Decoder.h"
#include "Encoder.h"

int main() {
  // CLI setup, get find out if user wants to compress or decompress and file to do it on
  int mode = 0;
  cout << "Make sure file/folder you want to compress/decompress in in current directory\n";
  cout << "Type 1 if you would like to compress or type 2 to decompress\n";
  cin >> mode;

  if (mode == 1) {
    cout << "Compression mode: Carefully type the full name of your file (including the .txt)\n";
    string filename = "";
    cin >> filename;
    Encoder encoder;
    ifstream txtFile(filename);
    if (!txtFile.is_open()) {
      cout << "Failed to open text file, make sure its spelled correctly (case sensitive)\n";
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
    ifstream txtFileCopy(filename);
    encoder.makeCompressedFolder(txtFileCopy);

    cout << "Compression complete! Your file 'compressed.txt' is in the folder 'compressed'\n";
    return 0;
  } else if (mode == 2) {
    cout << "Decompression mode. Looking for compressed folder" << endl;
    // Get serialized heap and make file for decompressing binary into text
    Decoder decoder;
    ifstream serializedHeap("compressed/serializedHeap.txt");
    ofstream decompressedTxtFile("decompressedTxtFile.txt");
    if (!serializedHeap.is_open()) {
      cout << "Failed to open compressed file, ensure the compressed folder is in this directory/n";
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
  } else {
    cout << "Please enter just 1 or 2\n";
    return -1;
  }
}
