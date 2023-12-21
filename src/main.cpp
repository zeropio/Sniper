#include <iostream>
#include <fstream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[]) {

    // Check user input file
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " filename" << endl;
        return 1;
    }

    // Open and check file
    const char* filename = argv[1];
    ifstream binary(filename, ios::binary);

    if (!binary) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    // Parsing
    parser_bin(hexdump(binary));

    // Searching (TODO)

    binary.close();
    return 0;
}
