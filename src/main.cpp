#include "Encode.h"
#include <memory>

int main() {
  // Make encoder, allocate for big files, stack might run out of memory
  unique_ptr<Encoder> encoder = make_unique<Encoder>();
  encoder->findCharOccurencesInFile(txtFile);
  cout << "running nicely!" << endl;
}
