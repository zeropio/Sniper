#include "common.h"
#include "parser.h"
#include "scanner.h"

int main(int argc, char* argv[]) {
    std::vector<SectionInfo> sections;

    // Welcome message
    std::cout << "--- Sniper Scanner Program ---" << std::endl;

    // Check user input
    if (argc < 3) {
        std::cerr << RED << "[-]" << RESET << " Usage: " << argv[0] << " <filename> <opcode/pattern>" << std::endl;
        std::cerr << RED << "[-]" << RESET << " Please provide a filename and a pattern to scan for." << std::endl;
        return 1;
    }

    // File and pattern information
    const char* filename = argv[1];
    const char* pattern = argv[2];
    std::cout << BLUE << "[?]" << RESET << " Scanning file: " << filename << std::endl;
    std::cout << BLUE << "[?]" << RESET << " Pattern to search for: " << pattern << std::endl;

    // Parsing the binary file
    std::cout << BLUE << "[?]" << RESET << " Parsing the binary file..." << std::endl;
    sections = parser_bin(filename);
    if (sections.empty()) {
        std::cerr << RED << "[-]" << RESET << " Failed to parse the file or no sections found." << std::endl;
        return 1;
    }
    std::cout << GREEN << "[+]" << RESET << " File parsed successfully. Found " << sections.size() << " sections." << std::endl;

    // Scanning for the pattern
    std::cout << BLUE << "[?]" << RESET << " Scanning for the pattern in the sections..." << std::endl;
    scanner(sections, pattern);

    std::cout << GREEN << "[+]" << RESET << " Scan complete." << std::endl;

    return 0;
}
