#include "Encode.h"

int main() {
  cout << "Type whether you would like to encode or decode, then the file or folder\n";
  cout << "Make sure file you want to compress/decompress in in current directory\n";

  // Make encoder, allocate for big files, stack might run out of memory
  unique_ptr<Encoder> encoder = make_unique<Encoder>();
  ifstream txtFile("../tests/textFiles/txt1.txt");
  encoder->createCharCountDict(txtFile);
}
