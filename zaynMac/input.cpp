//
//  input.cpp
//  zaynMac
//
//  Created by socki on 11/12/24.
//

#include "input.hpp"

#include <stdlib.h> // pulls in declaration of malloc, free
#include <string.h> // pulls in declaration for strlen.
#include <iostream>
#include "zayn.hpp"

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


InputKeyboardDiscrete GetInputKeyFromVirtualKey(unsigned short keyCode)
{
#if DEBUG
    std::cout << "keyCode: " << keyCode << std::endl;
#endif
    switch (keyCode)
    {
        case kVK_ANSI_A: return Input_A;
        case kVK_ANSI_B: return Input_B;
        case kVK_ANSI_C: return Input_C;
        case kVK_ANSI_D: return Input_D;
        case kVK_ANSI_E: return Input_E;
        case kVK_ANSI_F: return Input_F;
        case kVK_ANSI_G: return Input_G;
        case kVK_ANSI_H: return Input_H;
        case kVK_ANSI_I: return Input_I;
        case kVK_ANSI_J: return Input_J;
        case kVK_ANSI_K: return Input_K;
        case kVK_ANSI_L: return Input_L;
        case kVK_ANSI_M: return Input_M;
        case kVK_ANSI_N: return Input_N;
        case kVK_ANSI_O: return Input_O;
        case kVK_ANSI_P: return Input_P;
        case kVK_ANSI_Q: return Input_Q;
        case kVK_ANSI_R: return Input_R;
        case kVK_ANSI_S: return Input_S;
        case kVK_ANSI_T: return Input_T;
        case kVK_ANSI_U: return Input_U;
        case kVK_ANSI_V: return Input_V;
        case kVK_ANSI_W: return Input_W;
        case kVK_ANSI_X: return Input_X;
        case kVK_ANSI_Y: return Input_Y;
        case kVK_ANSI_Z: return Input_Z;
             // Numbers
        case kVK_ANSI_0: return Input_0;
        case kVK_ANSI_1: return Input_1;
        case kVK_ANSI_2: return Input_2;
        case kVK_ANSI_3: return Input_3;
        case kVK_ANSI_4: return Input_4;
        case kVK_ANSI_5: return Input_5;
        case kVK_ANSI_6: return Input_6;
        case kVK_ANSI_7: return Input_7;
        case kVK_ANSI_8: return Input_8;
        case kVK_ANSI_9: return Input_9;
             // Special keys
        case kVK_Space: return Input_Space;
        case kVK_Return: return Input_Return;
        case kVK_Tab: return Input_Tab;
        case kVK_Escape: return Input_Escape;
        case kVK_Delete: return Input_Backspace;
             // Arrow keys
        case kVK_UpArrow: return Input_UpArrow;
        case kVK_DownArrow: return Input_DownArrow;
        case kVK_LeftArrow: return Input_LeftArrow;
        case kVK_RightArrow: return Input_RightArrow;
             // Modifier keys
        case kVK_Shift: return Input_Shift;
        case kVK_Control: return Input_Control;
        case kVK_Option: return Input_Alt;
        case kVK_Command: return Input_LeftCommand;
             default: return Input_Invalid;
    }

}


void InputRegister(InputKeyboardDiscrete inputKey)
{
    InputEvent inputEvent = {};
    inputEvent.device = Zayn->keyboard;
    inputEvent.index = inputKey;
    inputEvent.discreteValue = true;
}
