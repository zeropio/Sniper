#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdint>
#include "parser.h"
#include "sniper.h"

void parser_bin(const char* filename) {
    HANDLE file = nullptr;
    DWORD fileSize = 0, bytesRead = 0;
    LPVOID fileData = nullptr;  // Change the type to LPVOID
    PIMAGE_DOS_HEADER dosHeader = nullptr;
    PIMAGE_NT_HEADERS imageNTHeaders = nullptr;
    PIMAGE_SECTION_HEADER sectionHeader = nullptr, importSection = nullptr;
    std::vector<PIMAGE_SECTION_HEADER> executableSections;
    std::string sectionContent;

    // Open and check
    file = CreateFileA(filename, GENERIC_READ, 0,
                       nullptr, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening file " << filename << ". Error code: " << GetLastError() << std::endl;
        return;
    }

    // Get file size
    fileSize = GetFileSize(file, nullptr);
    if (fileSize == INVALID_FILE_SIZE) {
        std::cerr << "Error getting file size. Error code: " << GetLastError() << std::endl;
        CloseHandle(file);
        return;
    }

    // Read the entire file into memory
    fileData = VirtualAlloc(nullptr, fileSize, MEM_COMMIT, PAGE_READWRITE);
    if (fileData == nullptr) {
        std::cerr << "Error allocating memory. Error code: " << GetLastError() << std::endl;
        CloseHandle(file);
        return;
    }

    if (!ReadFile(file, fileData, fileSize, &bytesRead,
                  nullptr)) {
        std::cerr << "Error reading file. Error code: " << GetLastError() << std::endl;
        VirtualFree(fileData, 0, MEM_RELEASE);
        CloseHandle(file);
        return;
    }

    // Initializations
    dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(fileData);
    imageNTHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(fileData) + dosHeader->e_lfanew);
    uintptr_t sectionLocation = reinterpret_cast<uintptr_t>(imageNTHeaders) + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER)
            + imageNTHeaders->FileHeader.SizeOfOptionalHeader;
    DWORD sectionSize = sizeof(IMAGE_SECTION_HEADER);
    DWORD importDirectoryRVA = imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]
            .VirtualAddress;

    // Executable Sections
    for (int i = 0; i < imageNTHeaders->FileHeader.NumberOfSections; i++) {
        sectionHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(reinterpret_cast<uintptr_t>(imageNTHeaders) +
                                                                sizeof(IMAGE_NT_HEADERS) +
                                                                i * sizeof(IMAGE_SECTION_HEADER));

        // Check if the section contains executable code
        if (sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE) {
            // Save the executable section
            executableSections.push_back(sectionHeader);
        }
    }

    for (const auto& execSection : executableSections) {
        // Calculate the offset from the beginning of the file data
        DWORD sectionOffset = execSection->PointerToRawData;
        DWORD sectionSize = execSection->SizeOfRawData;

        // Verbose
        std::cout << "Section name: " << execSection->Name << std::endl;
        std::cout << "Section offset: " << sectionOffset << std::endl;
        std::cout << "Section size: " << sectionSize << std::endl;

        // Print the content of the section
        for (DWORD offset = 0; offset < sectionSize; offset++) {
            char hexValue[3];  // Buffer for the two characters and null terminator
            sprintf(hexValue, "%02X", *(reinterpret_cast<uint8_t*>(fileData) + sectionOffset + offset));
            sectionContent += hexValue;
        }

        sniper(sectionContent);
        sectionContent.clear();
    }



    // Release resources
    VirtualFree(fileData, 0, MEM_RELEASE);
    CloseHandle(file);
}
