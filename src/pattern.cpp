#include "common.h"
#include "pattern.h"

enum ValidationResult {
    OPCODE,
    WILDCARD,
    INVALID
};

ValidationResult validation(const char* opcodes) {
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char wildcards[] = {'?', '*'};

    bool foundWildcard = false;
    bool foundValidOpcode = false;

    // Check for null ptr
    if (opcodes == nullptr) {
        std::cerr << "Error: opcodes pointer is null." << std::endl;
        return INVALID;
    }

    for (const char* ptr = opcodes; *ptr != '\0'; ++ptr) {
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
            std::cerr << "Error: " << *ptr << " is not a valid hex value or wildcard." << std::endl;
            return INVALID;
        }
    }

    if (foundWildcard) {
        return WILDCARD;
    } else if (foundValidOpcode) {
        return OPCODE;
    } else {
        // If no valid opcodes or wildcards are found, return INVALID
        return INVALID;
    }
}

void pattern_creation(const char* opcodes) {
    ValidationResult result = validation(opcodes);

    if (result == INVALID) {
        return;
    }

    if (result == WILDCARD) {
        return;
    }

    if (result == OPCODE) {
        return;
    }

};