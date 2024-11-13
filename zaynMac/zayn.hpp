////
////  zayn.hpp
////  zaynMac
////
////  Created by socki on 11/12/24.
////
////
//#ifndef zayn_hpp
//#define zayn_hpp
////
////
////
//#include <stdio.h>
//
//

//#include "input.hpp"
//
//

#pragma once


//#include "my_memory.hpp"
#include "data_types.h"
#include "my_memory.hpp"
//struct MemoryArena;

struct ZaynMemory
{
    int32 testInt;
    MemoryArena permanentMemArena;
    MemoryArena frameMemArena;

//    InputManager inputManager;
//    InputDevice* keyboard;
};

#ifdef __cplusplus
extern "C" {
#endif

void InitializeGame();
void UpdateLoop();


#ifdef __cplusplus
}
#endif
