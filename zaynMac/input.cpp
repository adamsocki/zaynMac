//
//  input.cpp
//  zaynMac
//
//  Created by socki on 11/19/24.
//

#include "input.hpp"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "zayn.hpp"

#include <Carbon/Carbon.h>
#include <CoreGraphics/CoreGraphics.h>

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




void InputRegister(ZaynMemory* zaynMem, InputKeyboardDiscrete inputKey, KeyAction action)
{
 
    
        if (action == KeyIsPressed)
        {
            InputEvent event = {};
            event.device = zaynMem->keyboard;
            event.index = inputKey;
            
            event.discreteValue = true;

            PushBack(&zaynMem->inputManager.events, event);

             std::cout << "Key pressed: " << inputKey << std::endl;
        }
        else if (action == KeyIsReleased)
        {
            InputEvent event = {};
            event.device = zaynMem->keyboard;
            event.index = inputKey;
            event.discreteValue = false;
            std::cout << "Key released: " << inputKey << std::endl;

            PushBack(&zaynMem->inputManager.events, event);

        }
}


void InputUpdate(ZaynMemory* zaynMem, InputManager* inputManager)
{
    for (int d = 0; d < inputManager->deviceCount; d++)
        {
            InputDevice* device = &inputManager->devices[d];

            if (device->type == InputDeviceType_Invalid) { continue; }

            for (int i = 0; i < device->discreteCount; i++)
            {
                device->released[i] = false;
                 //std::cout << "device->discretecount: " << i << std::endl;

                if (device->framesHeld[i] >= 0)
                {
                     //std::cout << "device->discretecount: " << i << std::endl;
                     //std::cout << "device->framesHeld[i]++: " << device->framesHeld[i] << std::endl;
                    device->framesHeld[i]++;
                    device->pressed[i] = false;
                }
            }
        }
    
    for (int i = 0; i < inputManager->events.count; i++)
        {
            // std::cout << "inputManager->events.count: " << i << std::endl;

            InputEvent event = inputManager->events[i];
            int32 index = event.index;

            InputDevice* device = event.device;

            if (!event.discreteValue)
            {
                if (device->framesHeld[index] > 0)
                {
                    device->released[index] = true;
                }
                device->timePressed[index] = -1;
                device->framesHeld[index] = -1;
                device->pressed[index] = false;
            }
            else
            {
                if (device->framesHeld[index] < 0)
                {
                     printf("pressed\n");
                    std::cout << "device->framesHeld" << std::endl;

                    device->timePressed[index] = zaynMem->time.zaynTime;
                    device->framesHeld[index] = 0;
                    device->pressed[index] = true;
                    device->released[index] = false;
                }
                else
                {
                    // @NOTE: we shouldnt even get a pressed event when the key is being held
                }
            }
        }

}


void ClearInputManager(InputManager* input)
{
    DynamicArrayClear(&input->events);

    input->charCount = 0;
    //memset(input->inputChars, 0, input->charSize);
}

bool InputHeld(InputDevice* device, int32 inputID)
{
    return device->framesHeld[inputID] > 0;
}

// Polling-based input implementation using Core Graphics
bool IsKeyPressed(InputKeyboardDiscrete key)
{
    // Map our input enum to Carbon virtual key codes
    CGKeyCode carbonKey = 0;
    switch (key)
    {
        case Input_W: carbonKey = kVK_ANSI_W; break;
        case Input_A: carbonKey = kVK_ANSI_A; break;
        case Input_S: carbonKey = kVK_ANSI_S; break;
        case Input_D: carbonKey = kVK_ANSI_D; break;
        case Input_Q: carbonKey = kVK_ANSI_Q; break;
        case Input_E: carbonKey = kVK_ANSI_E; break;
        default: return false;
    }
    
    // Check if the key is pressed using Core Graphics
    return CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, carbonKey);
}

void InputUpdatePolling(ZaynMemory* zaynMem)
{
    if (!zaynMem) return;
    
    // Update keyboard
    if (zaynMem->keyboard)
    {
        InputDevice* keyboard = zaynMem->keyboard;
        
        // Update keyboard state for WASD keys
        InputKeyboardDiscrete keys[] = {Input_W, Input_A, Input_S, Input_D, Input_Q, Input_E};
        
        for (int i = 0; i < 6; i++)
        {
            InputKeyboardDiscrete key = keys[i];
            bool isPressed = IsKeyPressed(key);
            
            if (isPressed)
            {
                if (keyboard->framesHeld[key] < 0)
                {
                    // Key just pressed
                    keyboard->framesHeld[key] = 0;
                    keyboard->pressed[key] = true;
                    keyboard->released[key] = false;
                }
                else
                {
                    // Key held
                    keyboard->framesHeld[key]++;
                    keyboard->pressed[key] = false;
                }
            }
            else
            {
                if (keyboard->framesHeld[key] >= 0)
                {
                    // Key just released
                    keyboard->released[key] = true;
                    keyboard->framesHeld[key] = -1;
                    keyboard->pressed[key] = false;
                }
            }
        }
    }
    
    // Update mouse (polling mouse position)
    if (zaynMem->inputManager.mouse)
    {
        InputDevice* mouse = zaynMem->inputManager.mouse;
        
        // Get current mouse position from system
        CGPoint mouseLocation = CGEventGetLocation(CGEventCreate(NULL));
        UpdateMousePosition(mouse, (real32)mouseLocation.x, (real32)mouseLocation.y);
        
        // Poll mouse buttons
        bool leftPressed = CGEventSourceButtonState(kCGEventSourceStateHIDSystemState, kCGMouseButtonLeft);
        bool rightPressed = CGEventSourceButtonState(kCGEventSourceStateHIDSystemState, kCGMouseButtonRight);
        bool middlePressed = CGEventSourceButtonState(kCGEventSourceStateHIDSystemState, kCGMouseButtonCenter);
        
        UpdateMouseButton(mouse, MouseButton_Left, leftPressed);
        UpdateMouseButton(mouse, MouseButton_Right, rightPressed);
        UpdateMouseButton(mouse, MouseButton_Middle, middlePressed);
    }
}

void UpdateMousePosition(InputDevice* mouse, real32 x, real32 y)
{
    MouseState* state = &mouse->mouseState;
    
    state->prevX = state->x;
    state->prevY = state->y;
    state->x = x;
    state->y = y;
    state->deltaX = x - state->prevX;
    state->deltaY = y - state->prevY;
}

void UpdateMouseButton(InputDevice* mouse, MouseButton button, bool pressed)
{
    MouseState* state = &mouse->mouseState;
    
    state->prevButtons[button] = state->buttons[button];
    state->buttons[button] = pressed;
    
    // Check for clicks and releases
    state->clicked[button] = pressed && !state->prevButtons[button];
    state->released[button] = !pressed && state->prevButtons[button];
}

bool IsMouseButtonPressed(InputDevice* mouse, MouseButton button)
{
    return mouse->mouseState.buttons[button];
}

bool IsMouseButtonClicked(InputDevice* mouse, MouseButton button)
{
    return mouse->mouseState.clicked[button];
}

bool IsMouseButtonReleased(InputDevice* mouse, MouseButton button)
{
    return mouse->mouseState.released[button];
}
