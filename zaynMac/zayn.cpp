//
//  zayn.cpp
//  zaynMac
//
//  Created by socki on 11/12/24.
//

#include "zayn.hpp"


#include "render_triangle.hpp"
#include "dynamic_array.hpp"


#include <iostream>


ZaynMemory* Zayn = NULL;

void InitializeGame() {
    // Initialize game state, load resources, etc.
    std::cout << "Game initialized!" << std::endl;
    
    ZaynMemory zaynMemory = {};
    Zayn = &zaynMemory;
    
    
    AllocateMemoryArena(&zaynMemory.permanentMemArena, Megabytes(256));
    AllocateMemoryArena(&zaynMemory.frameMemArena, Megabytes(32));

    
    
    InitTriangle();
}

void UpdateGame() {
    // Update game state, handle input, etc.
    std::cout << "Game updated!" << std::endl;
    RenderTriangle();
}
