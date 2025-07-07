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
    std::cout << "init Zayn - City Builder Mode" << std::endl;
    AllocateMemoryArena(&zaynMem->permanentMemArena, Megabytes(256));
    AllocateMemoryArena(&zaynMem->frameMemArena, Megabytes(32));
    
    AllocateInputManager(&zaynMem->inputManager, &zaynMem->permanentMemArena, 4);
    
    // Initialize keyboard device
    zaynMem->keyboard = &zaynMem->inputManager.devices[0];
    zaynMem->inputManager.keyboard = zaynMem->keyboard;
    AllocateInputDevice(zaynMem->keyboard, InputDeviceType_Keyboard, Input_KeyboardDiscreteCount, 0);
    
    // Initialize mouse device
    zaynMem->inputManager.mouse = &zaynMem->inputManager.devices[1];
    AllocateInputDevice(zaynMem->inputManager.mouse, InputDeviceType_Mouse, MouseButton_Count, 2); // 2 analog for x,y
    
    // Initialize city grid (20x20 tiles, 2 units per tile)
//    zaynMem->cityGrid = (GridSystem*)AllocateMem(&zaynMem->permanentMemArena, sizeof(GridSystem));
//    new (zaynMem->cityGrid) GridSystem();
//    InitializeGrid(zaynMem->cityGrid, &zaynMem->permanentMemArena, 20, 20, 2.0f);
    
    // Initialize scene
    zaynMem->currentScene = (Scene*)AllocateMem(&zaynMem->permanentMemArena, sizeof(Scene));
    new (zaynMem->currentScene) Scene(&zaynMem->permanentMemArena);
    
    // Scene will be populated from grid each frame
}


