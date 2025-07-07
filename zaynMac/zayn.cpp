//
//  zayn.cpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#include "zayn.hpp"
#include "constants.h"
#include <iostream>

// External game mode functions
extern "C" void InitializeGame(ZaynMemory* zaynMem);

void ZaynInit(ZaynMemory* zaynMem)
{
    // Display which game mode is active
    #if ACTIVE_GAME_MODE == GAME_MODE_CUBE_DEMO
        std::cout << "Initializing Zayn Engine - Cube Demo Mode" << std::endl;
    #elif ACTIVE_GAME_MODE == GAME_MODE_CITY_BUILDER
        std::cout << "Initializing Zayn Engine - City Builder Mode" << std::endl;
    #elif ACTIVE_GAME_MODE == GAME_MODE_LIGHTING_TEST
        std::cout << "Initializing Zayn Engine - Lighting Test Mode" << std::endl;
    #else
        std::cout << "Initializing Zayn Engine - Unknown Mode" << std::endl;
    #endif
    
    // Initialize core engine systems
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
    
    // Initialize game mode-specific systems
    InitializeGame(zaynMem);
}

// City builder functions (temporary implementations)
void UpdateCityBuilder(ZaynMemory* zaynMem, float deltaTime) {
    // Placeholder implementation
}

void UpdateSceneFromGrid(ZaynMemory* zaynMem) {
    // Placeholder implementation
}


