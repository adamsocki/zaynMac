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
//#include "my_memory.hpp"
//#include "input.hpp"
//
//
//struct ZaynMemory
//{
//    MemoryArena permanentMemArena;
//    MemoryArena frameMemArena;
//    
//    InputManager inputManager;
//    InputDevice* keyboard;
//};
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void InitializeGame();
void UpdateLoop();


#ifdef __cplusplus
}
#endif
