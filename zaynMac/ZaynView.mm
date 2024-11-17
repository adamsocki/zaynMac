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
#import "zayn.hpp"

@implementation ZaynView

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void) pollEventss{
    NSLog(@"testEVent");
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
            
            InputRegister(Zayn, inputKey, KeyIsPressed);
            
            #if DEBUG
            NSLog(@"Key pressed: %d -> %d", keyCode, inputKey);
            #endif
        }
}

- (void)keyUp:(NSEvent *)event {
//    [self processKeyEvent:event isKeyDown:NO];
    unsigned short keyCode = [event keyCode];
        InputKeyboardDiscrete inputKey = GetInputKeyFromVirtualKey(keyCode);
        
        if (inputKey != Input_Invalid) {
            
            InputRegister(Zayn, inputKey, KeyIsReleased);
            
            #if DEBUG
            NSLog(@"Key released: %d -> %d", keyCode, inputKey);
            #endif
        }

}

@end
