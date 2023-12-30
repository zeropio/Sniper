#include <regex>
#include "common.h"
#include "scanner.h"

int validation(const char* pattern) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                  'A', 'B', 'C', 'D', 'E', 'F'};

    // Check for null ptr
    if (pattern == nullptr) {
        std::cout << RED << "[-]" << RESET << " Null pattern provided." << std::endl;
        return 1;
    }

    try {
        std::regex tmp(pattern);
        std::cout << GREEN << "[+]" << RESET << " Regex pattern is valid." << std::endl;
        return 0;
    } catch (const std::regex_error&) {
        std::cout << BLUE << "[?]" << RESET << " Not a valid regex, checking as opcode." << std::endl;
    }

    bool foundValidOpcode = false;
    for (const char* ptr = pattern; *ptr != '\0'; ++ptr) {
        bool isValidHexChar = false;

        // Check for hex values in the input
        for (char c : hex) {
            if (toupper(*ptr) == c) {
                isValidHexChar = true;
                foundValidOpcode = true;
                break;
            }
        }

        if (!isValidHexChar) {
            std::cout << RED << "[-]" << RESET << " Invalid opcode pattern." << std::endl;
            return 1;
        }
    }

    std::cout << GREEN << "[+]" << RESET << " Opcode pattern is valid." << std::endl;
    return foundValidOpcode ? 0 : 1;
}

void scanner(const std::vector<SectionInfo>& sections, const char* pattern) {
    int result = validation(pattern);

    if (result == 1) {
        std::cout << RED << "[-]" << RESET << " Invalid pattern, aborting scan." << '\n';
        return;
    }

    for (const auto& section : sections) {
        std::regex regexPattern(pattern);
        std::smatch matches;

        std::cout << BLUE << "[?]" << RESET << " Scanning section " << section.name << std::endl;

        // Use regex search to find matches in section content
        if (std::regex_search(section.content, matches, regexPattern)) {
            unsigned int totalOffset = matches.position(0) + section.offset + section.baseAddress;

            std::cout << GREEN << "[+]" << RESET << " Pattern found in section " << section.name << std::endl;
            std::cout << GREEN << "[+]" << RESET << " Pattern found at hex address: 0x" << std::hex << totalOffset << std::endl;
        }
    }
};
