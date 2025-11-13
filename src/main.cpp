#include "Encode.h"

int main() {
  // CLI setup, get mode and filename to work on
  int mode = 0;
  cout << "Make sure file/folder you want to compress/decompress in in current directory\n";
  cout << "Type 1 if you would like to compress type 2 to decode, then the file or folder\n";
  // cin >> mode;
  mode = 1;

  if (mode == 1) {
    cout << "Compression mode: Carefully type the full name of your file (including the .txt)\n";
    string filename = "test.txt";
    // cin >> filename;
    //  Make encoder, dynamically allocate for big files, stack might run out of memory
    Encoder encoder;
    ifstream txtFile(filename);
    if (!txtFile.is_open()) {
      cout << "Failed to open text file, make sure its spelled correctly (case sensitive)\n";
      return -1;
    }

    // Now make the data structures we need to start compressing
    encoder.createCharCountDict(txtFile);
    encoder.createCharCountMinheap();
    // Don't compress empty files as that won't work with huffman tree
    if (encoder.m_minheap.m_charCountMinheap.size() == 0) {
      cout << "Empty minheap passed in\n";
      return -1;
    }
    /*
    encoder->createHuffmanTreeFromMinheap();

    // Now make codes and put it into a file in the compressed folder
    encoder->mapCharsToTreeCodes();
    encoder->turnCodesIntoBinaryFile();
    encoder->createAndInsertIntoCompressedFolder();
    */

    // If it works we now have a folder with binary data file and other file to decode it
    txtFile.close();
    cout << "Compression complete! Your file 'compressed.txt' is in the folder 'compressed'\n";
  } else if (mode == 2) {
    cout << "Decompression mode" << endl;
  } else {
    cout << "Please enter just 1 or 0\n";
    return -1;
  }
}
