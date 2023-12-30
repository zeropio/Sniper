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

#endif //SNIPER_COMMON_H
