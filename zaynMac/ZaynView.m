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

@implementation ZaynView

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)keyDown:(NSEvent *)event {
    NSString *characters = [event charactersIgnoringModifiers];
    unichar key = [characters characterAtIndex:0];

    if (key == 'w' || key == 'W') {
        NSLog(@"W key pressed");
    } else if (key == 's' || key == 'S') {
        NSLog(@"S key pressed");
    }
}

@end
