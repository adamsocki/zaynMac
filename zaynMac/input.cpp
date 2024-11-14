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

    inputManager->deviceCount = deviceCapacity;
    inputManager->devices = (InputDevice*)malloc(sizeof(InputDevice) * deviceCapacity);
    memset(inputManager->devices, 0, inputManager->deviceCount * sizeof(InputDevice));


}

void AllocateInputDevice(InputDevice *device, InputDeviceType type, int32 discreteCount, int32 analogueCount)
{
    device->type = type;
    device->discreteCount = discreteCount;

    device->framesHeld = (int32 *)malloc(sizeof(int32) * discreteCount);
    device->released = (bool *)malloc(sizeof(bool) * discreteCount);
    device->pressed = (bool *)malloc(sizeof(bool) * discreteCount);
    device->timePressed = (real32 *)malloc(sizeof(real32) * discreteCount);

    device->analogueCount = analogueCount;
    device->prevAnalogue = (real32 *)malloc(sizeof(real32) * analogueCount);
    device->analogue = (real32 *)malloc(sizeof(real32) * analogueCount);

    memset(device->framesHeld, -1, sizeof(int32) * discreteCount);
    memset(device->pressed, 0, sizeof(bool) * discreteCount);
    memset(device->released, 0, sizeof(bool) * discreteCount);
    memset(device->timePressed, 0, sizeof(real32) * discreteCount);

    memset(device->analogue, 0, sizeof(real32) * analogueCount);
    memset(device->prevAnalogue, 0, sizeof(real32) * analogueCount);
}

