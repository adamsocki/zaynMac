//////
//////  my_memory.cpp
//////  zaynMac
//////
//////  Created by socki on 11/12/24.
//////
////
#include "my_memory.hpp"
#include <iostream>

void AllocateMemoryArena(MemoryArena* arena, uint64 capacity)
{
    std::cout << "AllocateMemoryArena" << std::endl;
    void* (*allocate)(MemoryArena*, uint64) = &PushSizeMemoryArena;
    arena->allocate = (AllocateFunc*)allocate;
    arena->deallocate = NULL;
    arena->capacity = capacity;
    arena->size = 0;
    arena->ptr = malloc(capacity);
    memset(arena->ptr, 0, capacity);
}


void* PushSizeMemoryArena(MemoryArena* arena, uint64 size)
{
    void* result = (uint8*)arena->ptr + arena->size;
    arena->size += size;

    //ASSERT(arena->size < arena->capacity);

    return result;
}
