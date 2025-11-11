// To run this copy and paste this into terminal
/*
g++ -std=c++23 -Wall -Werror  testMakingCharCountDict.cpp ../../src/Encode.cpp && ./a.out
*/

#include "../../src/Encode.h"
#include <unordered_map>
#include <vector>

vector<unordered_map<string, int>> makeExpectedDicts() {
  vector<unordered_map<string, int>> expectedDicts;
  // When making expected dicts, order does not matter, just key value pairs
  unordered_map<string, int> expectedDict1 = {{"\\", 1}, {"!", 1}, {"/", 1}, {"$", 1}, {"&", 1},
                                              {"\n", 1}, {"*", 1}, {" ", 3}, {"o", 1}, {"b", 2}};
  // Push back first one twice to one index
  expectedDicts.push_back(expectedDict1);
  expectedDicts.push_back(expectedDict1);

  return expectedDicts;
}

void compareExpectedAndReturnedDicts(const unordered_map<string, int> &returned,
                                     const unordered_map<string, int> &expected, int &fails,
                                     int fileNum) {
  for (const auto &[ch, count] : returned) {
    cout << "'" << ch << "': " << count << '\n';
  }
  if (returned != expected) {
    cout << "❌ Test on file " << fileNum << " failed!" << endl;
    fails++;
    return;
  }
  cout << "✅ Test on file " << fileNum << " passed!" << endl;
}

int main() {
  // Make encoder, allocate for big files, stack might run out of memory
  unique_ptr<Encoder> encoder = make_unique<Encoder>();
  vector<unordered_map<string, int>> expectedDicts = makeExpectedDicts();

  // You can test files 1-10
  int filesToTest = 1;
  int fails = 0;
  for (int filenum = 1; filenum <= filesToTest; ++filenum) {
    string path = "../textFiles/txt" + to_string(filenum) + ".txt";
    ifstream txtFile(path);
    if (!txtFile) {
      cerr << "Failed to open file " << filenum << ". Exiting program" << endl;
      return 1;
    }
    encoder->createCharCountDict(txtFile);
    unordered_map<string, int> &charDict = encoder->getCharDict();
    compareExpectedAndReturnedDicts(charDict, expectedDicts[filenum], fails, filenum);
  }
  cout << filesToTest - fails << " out of " << filesToTest << " cases passed!\n";
}
