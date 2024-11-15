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

//
//

#pragma once


//#include "my_memory.hpp"
#include "data_types.h"
#include "my_memory.hpp"
//struct MemoryArena;
#include "input.hpp"
#include "time.hpp"



struct ZaynMemory
{
    int32 testInt;
    MemoryArena permanentMemArena;
    MemoryArena frameMemArena;

    InputManager inputManager;
    InputDevice* keyboard;
    
    ZaynTime time;
    
    
};

//#ifdef __cplusplus
//extern "C" {
//#endif

extern ZaynMemory* Zayn;
void InitializeGame();
void UpdateLoop();
void CleanUpZayn();


//#ifdef __cplusplus
//}
//#endif
