#include "Encode.h"

int main() {
  cout << "Type whether you would like to encode or decode, then the file or folder\n";
  // Make encoder, allocate for big files, stack might run out of memory
  unique_ptr<Encoder> encoder = make_unique<Encoder>();
  ifstream file("../tests/textFiles/txt1.txt");
  if (!file) {
    cerr << "Failed to open file :(" << endl;
    return 1;
  }

  // encoder->findCharOccurencesInFile(txtFile);
  cout << "running nicely!" << endl;
}
