#include "common.h"
#include "parser.h"
#include "scanner.h"

int main(int argc, char* argv[]) {
    std::vector<SectionInfo> sections;

    // Check user input
    if (argc < 3) {
        std::cerr << "Usage: " <<  "filename opcode" << std::endl;
        return 1;
    }

    // Open and check file
    const char* filename = argv[1];
    const char* opcodes = argv[1];

    // Sections and pattern preparation
    sections = parser_bin(filename);

    // Scan
    scanner(sections, opcodes);

    return 0;
}
