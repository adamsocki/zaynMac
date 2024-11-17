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
#include <chrono>
#include <cstdio>


ZaynMemory* Zayn = NULL;



void InitializeGame() {
    // Initialize game state, load resources, etc.
    std::cout << "Game initialized!" << std::endl;
    
    Zayn = new ZaynMemory();
    Zayn->testInt = 20;
//    int32 test2 = 22;
//    Zayn = &zaynMemory;
    clock_gettime(CLOCK_MONOTONIC, &Zayn->time.spec);
    Zayn->time.startTime = (Zayn->time.spec.tv_sec * 1000.0) + (Zayn->time.spec.tv_nsec / 1.0e6);
    
       

        Zayn->time.zaynTime = 0.0;
        Zayn->time.systemTime = Zayn->time.startTime;
//        double prevSystemTime = systemTime;
//        double deltaTime;

        // seconds
//        double frameRate = 1.0 / 6000.0; // Hertz
//        double timeSinceRender = 0.0;
    
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
        // HANDLE TIME
    clock_gettime(CLOCK_MONOTONIC, &Zayn->time.spec);
    Zayn->time.systemTime = (Zayn->time.spec.tv_sec * 1000.0) + (Zayn->time.spec.tv_nsec / 1.0e6);
    Zayn->time.deltaTime = (Zayn->time.systemTime - Zayn->time.prevSystemTime) / 1000.0;
    Zayn->time.prevSystemTime = Zayn->time.systemTime;

    Zayn->time.zaynTime = (Zayn->time.systemTime - Zayn->time.startTime) / 1000.0;
    Zayn->time.timeSinceRender += Zayn->time.deltaTime;
    
    printf("zaynTime %.6f\n" , Zayn->time.zaynTime);
    printf("deltaTime %.6f\n", Zayn->time.deltaTime);

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
    
//    if (InputHeld(Zayn->keyboard, Input_U))
//    {
//        std::cout << "Input_U" << std::endl;
//    }
//    clock_gettime(CLOCK_MONOTONIC, &spec);
   // systemTime = (spec.tv_sec * 1000.0) + (spec.tv_nsec
    
    
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
