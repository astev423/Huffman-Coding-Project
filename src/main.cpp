#include "Decoder.h"
#include "Encoder.h"

int main() {
  // CLI setup, get find out if user wants to compress or decompress and file to do it on
  int mode = 0;
  int exitCode = 0;
  cout << "Make sure file/folder you want to compress/decompress in in current directory\n";
  cout << "Type 1 if you would like to compress or type 2 to decompress\n";
  cin >> mode;

  // Encoder/Decoder class perform all necessary logic and return 0 if successful or -1 if not
  if (mode == 1) {
    Encoder encoder;
    exitCode = encoder.encode();
  } else if (mode == 2) {
    Decoder decoder;
    exitCode = decoder.decode();
  } else {
    cout << "Please enter just 1 or 2\n";
    exitCode = -1;
  }

  return exitCode;
}
