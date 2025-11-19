#include "../../src/Encoder.h"
#include <unordered_map>
#include <vector>

void makeExpectedDictsAndCharCounts(vector<unsigned>& expectedTotalChars,
                                    vector<unordered_map<string, unsigned>>& expectedDicts);
void compareExpectedAndReturnedValues(const unordered_map<string, unsigned>& returnedDicts,
                                      const unordered_map<string, unsigned>& expectedDicts,
                                      unsigned returnedCharCount, unsigned expectedCharCount,
                                      unsigned& fails, unsigned fileNum);

int main() {
  Encoder encoder;
  vector<unordered_map<string, unsigned>> expectedDicts;
  vector<unsigned> expectedTotalChars;
  makeExpectedDictsAndCharCounts(expectedTotalChars, expectedDicts);

  // You can test files 1-9
  unsigned filesToTest = 9;
  unsigned fails = 0;
  for (unsigned filenum = 1; filenum <= filesToTest; ++filenum) {
    string path = "../textFiles/txt" + to_string(filenum) + ".txt";
    ifstream txtFile(path);
    if (!txtFile) {
      cerr << "Failed to open file " << filenum << ". Exiting program" << endl;
      return 1;
    }
    encoder.createCharCountDict(txtFile);

    // After creating dict from file compare it to expected and reset values for next file
    compareExpectedAndReturnedValues(encoder.getCharDict(), expectedDicts[filenum],
                                     encoder.getTotalCharCount(), expectedTotalChars[filenum],
                                     fails, filenum);
    encoder.resetDict();
    encoder.resetCharCount();
  }
  cout << filesToTest - fails << " out of " << filesToTest << " cases passed!\n";
}

void makeExpectedDictsAndCharCounts(vector<unsigned>& expectedTotalChars,
                                    vector<unordered_map<string, unsigned>>& expectedDicts) {
  // When making expected dicts, order does not matter, just key value pairs
  // Below is all our expected dictionary key value pairs and the char count for each
  unordered_map<string, unsigned> expectedDict1 = {{"\\", 1}, {"!", 1},  {"/", 1}, {"$", 1},
                                                   {"&", 1},  {"\n", 1}, {"*", 1}, {" ", 3},
                                                   {"o", 1},  {"b", 2}};
  expectedDicts.push_back(expectedDict1);
  expectedDicts.push_back(expectedDict1);
  expectedTotalChars.push_back(13);
  expectedTotalChars.push_back(13);
  unordered_map<string, unsigned> expectedDict2 = {{"b", 1}, {"i", 1}, {"l", 2}, {"p", 2},
                                                   {"o", 1}, {"1", 1}, {"2", 1}, {"3", 1},
                                                   {"!", 1}, {"\n", 5}};
  expectedDicts.push_back(expectedDict2);
  expectedTotalChars.push_back(16);
  unordered_map<string, unsigned> expectedDict3 = {
      {"\n", 112}, {" ", 605}, {"!", 21},  {"\"", 2},  {"'", 39},  {",", 45},  {"-", 6},
      {".", 92},   {"0", 3},   {"1", 3},   {"2", 1},   {"5", 1},   {"7", 1},   {"8", 1},
      {"9", 1},    {":", 1},   {"?", 24},  {"A", 12},  {"B", 15},  {"C", 6},   {"D", 2},
      {"E", 2},    {"F", 2},   {"G", 2},   {"H", 24},  {"I", 20},  {"J", 2},   {"K", 3},
      {"L", 4},    {"M", 2},   {"N", 6},   {"O", 5},   {"P", 3},   {"R", 2},   {"S", 8},
      {"T", 17},   {"U", 1},   {"V", 1},   {"W", 23},  {"Y", 14},  {"a", 224}, {"b", 47},
      {"c", 88},   {"d", 93},  {"e", 377}, {"f", 49},  {"g", 58},  {"h", 138}, {"i", 156},
      {"j", 11},   {"k", 48},  {"l", 146}, {"m", 58},  {"n", 171}, {"o", 272}, {"p", 38},
      {"q", 3},    {"r", 148}, {"s", 166}, {"t", 245}, {"u", 107}, {"v", 35},  {"w", 69},
      {"x", 7},    {"y", 88},  {"z", 6}};
  expectedDicts.push_back(expectedDict3);
  expectedTotalChars.push_back(3982);
  unordered_map<string, unsigned> expectedDict4 = {
      {"\n", 21}, {"#", 1}, {"$", 2}, {"%", 2}, {"&", 4}, {"(", 3}, {"*", 5}, {"1", 1},
      {"2", 3},   {"3", 2}, {"4", 4}, {"5", 1}, {"6", 1}, {"7", 1}, {"8", 5}, {"9", 5},
      {"@", 2},   {"a", 1}, {"d", 6}, {"e", 2}, {"f", 6}, {"h", 2}, {"i", 2}, {"j", 6},
      {"k", 2},   {"n", 3}, {"o", 1}, {"s", 3}, {"u", 1}, {"w", 2}, {"z", 4},
  };
  expectedDicts.push_back(expectedDict4);
  expectedTotalChars.push_back(104);
  unordered_map<string, unsigned> expectedDict5 = {
      {"\n", 12}, {" ", 2}, {"=", 27}, {"d", 1}, {"e", 5}, {"f", 1}, {"h", 1}, {"i", 2},
      {"m", 1},   {"n", 2}, {"o", 4},  {"r", 4}, {"s", 1}, {"u", 2}, {"w", 3}};
  expectedDicts.push_back(expectedDict5);
  expectedTotalChars.push_back(68);
  unordered_map<string, unsigned> expectedDict6 = {
      {"\n", 1}, {" ", 3}, {"!", 2}, {"(", 1}, {")", 1}, {"@", 2}, {"?", 2}, {"a", 1},
      {"b", 1},  {"h", 1}, {"i", 2}, {"k", 2}, {"l", 1}, {"n", 3}, {"o", 1}, {"t", 2}};
  expectedDicts.push_back(expectedDict6);
  expectedTotalChars.push_back(26);
  unordered_map<string, unsigned> expectedDict7 = {{"i", 1}, {"\n", 1}};
  expectedDicts.push_back(expectedDict7);
  expectedTotalChars.push_back(2);
  unordered_map<string, unsigned> expectedDict8 = {{"?", 1}, {"\n", 1}};
  expectedDicts.push_back(expectedDict8);
  expectedTotalChars.push_back(2);
  unordered_map<string, unsigned> expectedDict9 = {{"a", 22000}, {"\n", 2200}};
  expectedDicts.push_back(expectedDict9);
  expectedTotalChars.push_back(24200);
}

void compareExpectedAndReturnedValues(const unordered_map<string, unsigned>& returnedDict,
                                      const unordered_map<string, unsigned>& expectedDict,
                                      unsigned returnedCharCount, unsigned expectedCharCount,
                                      unsigned& fails, unsigned fileNum) {
  bool failed = false;
  // printing key value pairs for debugging
  //  for (const auto &[ch, count] : returnedDict) {
  //    cout << "'" << ch << "': " << count << '\n';
  //  }
  if (returnedDict != expectedDict) {
    cout << "Dictionaries dont match!\n";
    failed = true;
  }
  if (returnedCharCount != expectedCharCount) {
    cout << "Char count of " << returnedCharCount << " doesn't match " << expectedCharCount << endl;
    failed = true;
  }
  if (failed) {
    cout << "❌ Test on file " << fileNum << " failed!" << endl;
    fails++;
    return;
  }

  cout << "✅ Test on file " << fileNum << " passed!" << endl;
}
