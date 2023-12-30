#include <regex>
#include "common.h"
#include "scanner.h"

int validation(const char* pattern) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                  'A', 'B', 'C', 'D', 'E', 'F'};
    bool foundValidOpcode = false;

    // Check for null ptr
    if (pattern == nullptr) {
        return 1;
    }

    try {
        std::regex tmp(pattern);
        return 0;
    } catch (const std::regex_error&) {
        // Not a valid regex, proceed to check if it's a valid opcode
    }

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
            return 1;
        }
    }

    return foundValidOpcode ? 0 : 1;
}

void scanner(const std::vector<SectionInfo>& sections, const char* pattern) {
    int result = validation(pattern);


    if (result == 1) {
        std::cout << "Invalid pattern" << '\n';
        return;
    }

    for (const auto& section : sections) {
        std::regex regexPattern(pattern);
        std::smatch matches;

        // Use regex search to find matches in section content
        if (std::regex_search(section.content, matches, regexPattern)) {
            unsigned int totalOffset = matches.position(0) + section.offset + section.baseAddress;

            std::cout << "Opcode found in section " << section.name << std::endl;
            std::cout << "Pattern found at hex address: 0x" << std::hex << totalOffset << std::endl;
        }
    }
};
