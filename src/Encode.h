#ifndef ENCODE_H
#define ENCODE_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

class Encoder {
private:
  // This doesn't have to be allocated as it just holds ascii unique chars and ints for them
  unordered_map<string, int> charsAndTheirOccurences;

public:
  void createCharCountDict(ifstream &txtFile);
  unordered_map<string, int> &getCharDict();
};
#endif
