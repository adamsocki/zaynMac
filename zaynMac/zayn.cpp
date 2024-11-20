//
//  zayn.cpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#include "zayn.hpp"
#include <iostream>



void ZaynInit(ZaynMemory* zaynMem)
{
    std::cout << "init Zayn" << std::endl;
    AllocateMemoryArena(&zaynMem->permanentMemArena, Megabytes(256));
    AllocateMemoryArena(&zaynMem->frameMemArena, Megabytes(32));
    
//    InputManager* inputManager = &zaynMem->inputManager;
    AllocateInputManager(&zaynMem->inputManager, &zaynMem->permanentMemArena, 4);


}


