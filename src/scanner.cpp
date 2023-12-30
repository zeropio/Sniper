#include <regex>
#include "common.h"
#include "scanner.h"

enum ValidationResult {
    OPCODE,
    REGEX,
    INVALID
};

ValidationResult validation(const char* pattern) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    bool foundValidOpcode = false;

    // Check for null ptr
    if (pattern == nullptr) {
        return INVALID;
    }

    try {
        std::regex tmp(pattern);
        return REGEX;
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
            return INVALID;
        }
    }

    return foundValidOpcode ? OPCODE : INVALID;
}

void scanner(const std::vector<SectionInfo>& sections, const char* pattern) {
    ValidationResult result = validation(pattern);


    if (result == INVALID) {
        std::cout << "Invalid pattern" << '\n';
        return;
    }

    for (const auto& section : sections) {
        if (result == REGEX) {
            std::regex regexPattern(pattern);

            // Use regex search to find matches in section content
            if (std::regex_search(section.content, regexPattern)) {
                std::cout << "Regex pattern found in section " << section.name << '\n';
            }
            // Using continue to ensure all sections are searched
            continue;
        }

        if (result == OPCODE) {
            if (section.content.find(pattern) != std::string::npos) {
                std::cout << "Opcode found in section!" << '\n';
            }
            // Using continue to ensure all sections are searched
            continue;
        }
    }
};
