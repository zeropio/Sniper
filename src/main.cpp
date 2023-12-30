#include "common.h"
#include "parser.h"
#include "scanner.h"

int main(int argc, char* argv[]) {
    std::vector<SectionInfo> sections;

    // Check user input
    if (argc < 2) {
        std::cerr << "Usage: " <<  "filename opcode" << std::endl;
        return 1;
    }

    // Open and check file
    const char* filename = argv[1];
    const char* pattern = argv[2];

    // Sections and pattern preparation
    sections = parser_bin(filename);
    if (sections.empty()) {
        std::cerr << "No sections found or error parsing the file." << std::endl;
        return 1;
    }

    // Scan
    scanner(sections, pattern);

    return 0;
}
