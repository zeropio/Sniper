#include "common.h"
#include "scanner.h"

enum ValidationResult {
    OPCODE,
    WILDCARD,
    INVALID
};

ValidationResult validation(const char* pattern) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                  'B', 'C', 'D', 'E', 'F'};
    char wildcards[] = {'?', '*'};

    bool foundWildcard = false;
    bool foundValidOpcode = false;

    // Check for null ptr
    if (pattern == nullptr) {
        std::cerr << "Error: pattern pointer is null." << std::endl;
        return INVALID;
    }

    for (const char* ptr = pattern; *ptr != '\0'; ++ptr) {
        bool isValidHexChar = false;

        // Check for hex values on input
        for (char c : hex) {
            if (toupper(*ptr) == c) {
                isValidHexChar = true;
                foundValidOpcode = true;
                break;
            }
        }

        // Check for wildcards values on input
        for (char w : wildcards) {
            if (*ptr == w) {
                foundWildcard = true;
                break;
            }
        }

        // Final check
        if (!isValidHexChar && !foundWildcard) {
            return INVALID;
        }
    }

    if (foundWildcard) {
        return WILDCARD;
    } else if (foundValidOpcode) {
        return OPCODE;
    } else {
        // If no valid opcodes or wildcards are found, return INVALID
        std::cerr << "Error: " << pattern << " is not a valid hex value or wildcard." << std::endl;
        return INVALID;
    }
}

void scanner(const std::vector<SectionInfo>& sections, const char* pattern) {
    /*
    for (const auto& section : sections) {
        std::cout << "Section Name: " << section.name << std::endl;
        std::cout << "Content: " << section.content << std::endl;
        std::cout << "Testing content of section against pattern " << pattern
                  << ": " << (match(section.content.c_str(), pattern) ? "Match" : "No match") << std::endl;
    }
     */
    ValidationResult result = validation(pattern);

    if (result == INVALID) {
        return;
    }

    for (const auto& section : sections) {

        if (result == WILDCARD) {

            return;
        }

        if (result == OPCODE) {
            if (section.content.find(pattern) != std::string::npos) {
                std::cout << "found!" << '\n';
            }
                return;
        }

    }

};