#include "common.h"
#include "parser.h"
#include "scanner.h"
#include "pattern.h"

int main(int argc, char* argv[]) {
    std::vector<SectionInfo> sections;

    // Check user input
    if (argc < 2) {
        std::cerr << "Usage: " <<  "filename opcode" << std::endl;
        return 1;
    }

    // Open and check file
    const char* filename = argv[1];
    const char* opcodes = argv[2];

    // Sections and pattern preparation
    sections = parser_bin(filename);
    pattern_creation(opcodes);

    // Scan
    scanner(sections, opcodes);

    return 0;
}
