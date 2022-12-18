#pragma once
#include <iostream>

#ifdef _DEBUG
size_t allocated = 0;

void* operator new(size_t size) {
    allocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    allocated -= size;
    free(memory);
}

// 192 bytes from ModelGeometries Map
#define _CHECKLEAKS if (allocated) { std::cout << "[MEMORY LEAK!]: " << allocated << " bytes of allocated memory still remain!" << std::endl; }

#else

#define _CHECKLEAKS

#endif