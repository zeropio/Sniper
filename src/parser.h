#ifndef SNIPER_PARSER_H
#define SNIPER_PARSER_H

#include <fstream>
using namespace std;

basic_string<char> hexdump(ifstream& inputFile);
void parser_bin(basic_string<char>); //TODO

#endif //SNIPER_PARSER_H
