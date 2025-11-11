#include "Encode.h"

// First open a file
// dynamically allocate dictionary because it will take up a lot of space

int main() {
  std::ifstream file("filename.txt");
  std::string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      std::cout << line << '\n';
    }
    file.close();
  } else {
    std::cerr << "Error: Unable to open file.\n";
  }

  return 0;
}
