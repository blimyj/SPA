#pragma once
<<<<<<< HEAD
using namespace std;
int Parse();
=======

#include <vector>
#include <string>

typedef std::string STRING;
typedef std::vector<std::string> LIST_OF_STRINGS;

int Parse();
int parseFile(STRING);
int parseText(LIST_OF_STRINGS);
<<<<<<< HEAD
>>>>>>> Change Parser assumptions
=======

int parsePrint(STRING str, int ind);
int parseRead(STRING str, int ind);

STRING getNextToken(std::istreambuf_iterator<char>* iter, std::istreambuf_iterator<char> eos);
>>>>>>> Add tokenization to parser
