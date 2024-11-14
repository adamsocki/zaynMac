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
    [self processKeyEvent:event isKeyDown:YES];
    
    
    
    //    GetInputKeyFromVirtualKey([event keyCode]);
    
    NSString *characters = [event charactersIgnoringModifiers];
    if ([characters length] > 0)
    {
        
                
    }
    
        
    //    if (key == 'w' || key == 'W') {
    //        NSLog(@"W key pressed");
    //    } else if (key == 's' || key == 'S') {
    //        NSLog(@"S key pressed");
    //    }
}

- (void)keyUp:(NSEvent *)event {
    [self processKeyEvent:event isKeyDown:NO];
}

@end
