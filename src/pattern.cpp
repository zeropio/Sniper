#include "common.h"
#include "pattern.h"

int validation(const char* opcodes) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
                  'B', 'C', 'D', 'E', 'F'};
    char wildcards[] = {'?', '*'};

    // Check if the opcodes pointer is not null
    if (opcodes == nullptr) {
        std::cerr << "Error: opcodes pointer is null." << std::endl;
        return 1;
    }

    // Iterate through each character in the string until the null character
    for (const char* ptr = opcodes; *ptr != '\0'; ++ptr) {
        bool isValidHexChar = false;
        bool isValidWildcardChar = false;

        // Check if the current character is a valid hex character
        for (char c : hex) {
            if (toupper(*ptr) == c) {
                isValidHexChar = true;
                break;
            }
        }

        // Check if the current character is a valid wildcard character
        for (char w : wildcards) {
            if (toupper(*ptr) == w) {
                isValidWildcardChar = true;
                break;
            }
        }

        // If the character is not a valid hex value or wildcard, return an error code
        if (!isValidHexChar && !isValidWildcardChar) {
            std::cerr << "Error: " << *ptr << " is not a valid hex value or wildcard." << std::endl;
            return 1;
        }
    }

    return 0;
};

void pattern_creation(const char* opcodes) {
    if (validation(opcodes) == 1) {
        return;
    }

    return;
};