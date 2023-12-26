#include "common.h"
#include "parser.h"
#include "scanner.h"

int main(int argc, char* argv[]) {
    std::vector<SectionInfo> sections;

    // Check user input file
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    // Open and check file
    const char* filename = argv[1];
    sections = parser_bin(filename);

    return 0;
}
