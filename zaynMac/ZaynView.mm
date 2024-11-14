////
////  MyView.m
////  zaynMac
////
////  Created by socki on 11/12/24.
////
//
//#import <Foundation/Foundation.h>
//
//
//// MyView.m
#import "ZaynView.hpp"
#import "input.hpp"

@implementation ZaynView

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void) processKeyEvent:(NSEvent*)event isKeyDown:(BOOL)isKeyDown
{
    unsigned short keyCode = [event keyCode];
    InputKeyboardDiscrete inputKey = GetInputKeyFromVirtualKey(keyCode);
#if DEBUG
    NSLog(@"k %u", inputKey);
#endif
    
}


- (void)keyDown:(NSEvent *)event
{
    unsigned short keyCode = [event keyCode];
        InputKeyboardDiscrete inputKey = GetInputKeyFromVirtualKey(keyCode);
        
        if (inputKey != Input_Invalid) {
            
            InputRegister(inputKey);
            
//            InputEvent inputEvent = {};
//            inputEvent.device = Zayn->keyboard;
//            inputEvent.index = inputKey;
//            inputEvent.discreteValue = true;  // Key is pressed
//            PushBack(&Zayn->inputManager->events, inputEvent);
//            
            #if DEBUG
            NSLog(@"Key pressed: %d -> %d", keyCode, inputKey);
            #endif
        }
}

- (void)keyUp:(NSEvent *)event {
    [self processKeyEvent:event isKeyDown:NO];
}

@end
