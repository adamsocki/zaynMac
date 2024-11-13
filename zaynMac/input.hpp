//
//  input.hpp
//  zaynMac
//
//  Created by socki on 11/12/24.
//

#ifndef input_hpp
#define input_hpp

#include <stdio.h>

#include "data_types.h"
#include "dynamic_array.hpp"

enum InputDeviceType
{
    InputDeviceType_Invalid,
    InputDeviceType_Keyboard,
    InputDeviceType_Mouse,
};

struct InputDevice
{
    InputDeviceType type;

    int32 discreteCount;

    int32* framesHeld;
    bool* released;
    bool* pressed;
    real32* timePressed;

    int32 analogueCount;

    real32* prevAnalogue;
    real32* analogue;
};


struct InputEvent
{
    InputDevice* device;
    int32 index;
    bool discreteValue;
    real32 value;

};

struct InputManager
{
    int32 deviceCount;
    InputDevice* devices;

   // DynamicArray<InputEvent> events;

    uint32 charCount;



};

#endif /* input_hpp */
