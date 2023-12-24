#include <iostream>
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
    parser_bin(filename);

    return 0;
}
