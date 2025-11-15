#include "Decoder.h"
#include "Encode.h"

int main() {
  // CLI setup, get find out if user wants to compress or decompress and file to do it on
  int mode = 0;
  cout << "Make sure file/folder you want to compress/decompress in in current directory\n";
  cout << "Type 1 if you would like to compress or type 2 to decode\n";
  // cin >> mode;
  mode = 2;

  if (mode == 1) {
    cout << "Compression mode: Carefully type the full name of your file (including the .txt)\n";
    string filename = "beatsRLE.txt";
    // cin >> filename;
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

    // After making data structures we can now get codes
    encoder.createCharCodeDict();

    // Finally add codes to binary file + serialize heap for decompression and put both in a folder
    // For reasons I don't understand reusing the txtFile causes program to break so make copy
    ifstream txtFileCopy(filename);
    encoder.makeCompressedFolder(txtFileCopy);

    txtFile.close();
    cout << "Compression complete! Your file 'compressed.txt' is in the folder 'compressed'\n";
  } else if (mode == 2) {
    cout << "Decompression mode. Looking for compressed folder" << endl;
    Decoder decoder;
    ifstream binaryFile("compressed/serializedHeap.txt");
    if (!binaryFile.is_open()) {
      cout << "Failed to open compressed file, ensure the compressed folder is in this directory/n";
      return -1;
    }

    decoder.deserializeMinheap(binaryFile);
  } else {
    cout << "Please enter just 1 or 0\n";
    return -1;
  }
}
