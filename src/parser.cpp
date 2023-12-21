#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "parser.h"

basic_string<char> hexdump(std::ifstream& inputFile) {
    char byte;
    std::stringstream hexdump;
    int count = 0;

    // Set the stream position to the beginning of the file
    inputFile.seekg(0, std::ios::beg);

    // Save the string
    while (inputFile.get(byte)) {
        // Append the hexadecimal representation to the stringstream
        hexdump << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)byte;
        hexdump << " ";
        count++;
    }

    // Return hexdump string
    return hexdump.str();
}
