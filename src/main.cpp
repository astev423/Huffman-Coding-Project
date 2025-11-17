#include "Decoder.h"
#include "Encoder.h"
#include <iostream>

int main() {
  // CLI setup: determine whether the user wants to compress or decompress
  int mode = 0;
  int exitCode = 0;
  std::cout << "Make sure file/folder you want to compress/decompress is in current directory\n";
  std::cout << "Type 1 to compress or 2 to decompress\n";
  std::cin >> mode;

  // Encoder/Decoder classes perform all necessary logic and return 0 if successful or -1 on failure
  if (mode == 1) {
    Encoder encoder;
    exitCode = encoder.encode();
  } else if (mode == 2) {
    Decoder decoder;
    exitCode = decoder.decode();
  } else {
    std::cout << "Please enter only the integers 1 or 2\n";
    exitCode = -1;
  }

  return exitCode;
}
