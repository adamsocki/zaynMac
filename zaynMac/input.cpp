//
//  input.cpp
//  zaynMac
//
//  Created by socki on 11/12/24.
//

#include "input.hpp"

#include <stdlib.h> // pulls in declaration of malloc, free
#include <string.h> // pulls in declaration for strlen.

void AllocateInputManager(InputManager* inputManager, MemoryArena* arena, int32 deviceCapacity)
{
    inputManager->events = MakeDynamicArray<InputEvent>(arena, deviceCapacity);
//
//    inputManager->deviceCount = deviceCapacity;
//    inputManager->devices = (InputDevice*)malloc(sizeof(InputDevice) * deviceCapacity);
//    memset(inputManager->devices, 0, inputManager->deviceCount * sizeof(InputDevice));


}
