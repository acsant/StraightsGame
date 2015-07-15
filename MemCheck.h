//
// Created by Akash Sant on 15-07-12.
//

#ifndef STRAIGHTS_MEMCHECK_H
#define STRAIGHTS_MEMCHECK_H

#include <cstddef>

void* operator new(std::size_t, const char*, long);
void* operator new[](std::size_t, const char*, long);
#define new new (__FILE__, __LINE__)

extern bool traceFlag;
#define TRACE_ON() traceFlag = false
#define TRACE_OFF() traceFlag = false

extern bool activeFlag;
#define MEM_ON() activeFlag = true
#define MEM_OFF() activeFlag = false

#endif //STRAIGHTS_MEMCHECK_H
