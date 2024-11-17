////
////  zayn.cpp
////  zaynMac
////
////  Created by socki on 11/12/24.
////
//
#include "zayn.hpp"
//
//
//#include "render_triangle.hpp"
//#include "dynamic_array.hpp"
#include <stdlib.h> // pulls in declaration of malloc, free
#include <string.h> // pulls in declaration for strlen.

#include <iostream>


ZaynMemory* Zayn = NULL;

void InitializeGame() {
    // Initialize game state, load resources, etc.
    std::cout << "Game initialized!" << std::endl;
    
    Zayn = new ZaynMemory();
    Zayn->testInt = 20;
//    int32 test2 = 22;
//    Zayn = &zaynMemory;
    
    
    AllocateMemoryArena(&Zayn->permanentMemArena, Megabytes(256));
    AllocateMemoryArena(&Zayn->frameMemArena, Megabytes(32));

    InputManager* inputManager = &Zayn->inputManager;


    AllocateInputManager(inputManager, &Zayn->permanentMemArena, 4);
        
    Zayn->keyboard = &inputManager->devices[0];
    AllocateInputDevice(Zayn->keyboard, InputDeviceType_Keyboard, Input_KeyboardDiscreteCount, 0);
        
    //Keyboard = zaynMemory->keyboard;
    //InitializeKeyMap();
    

    
//    InitTriangle();
}

void UpdateGame() {
    // Update game state, handle input, etc.
//    while 
//    std::cout << "Game updated!" << std::endl;
//    int32 a = 11;
//    for (int i = 0; i < 1222; i++)
//    {
//        int32 test = 10;
//        a += test;
//    }
    InputUpdate(&Zayn->inputManager);
//    RenderTriangle();
    
    ClearInputManager(&Zayn->inputManager);
}

void CleanUpZayn()
{
    if (Zayn)
    {
        free(Zayn);
        Zayn = NULL;
    }
}
