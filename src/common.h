#ifndef SNIPER_COMMON_H
#define SNIPER_COMMON_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdint>

struct SectionInfo {
    std::string name;
    DWORD baseAddress;
    DWORD offset;
    DWORD size;
    std::string content;
};

// ANSI escape codes for colors
const char* const RESET = "\033[0m";
const char* const RED = "\033[31m";
const char* const GREEN = "\033[32m";
const char* const BLUE = "\033[33m";

#endif //SNIPER_COMMON_H
