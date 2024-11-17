 
// AppDelegate.mm
#import "AppDelegate.h"
#import "MetalSetup.h"
#import "zayn.hpp"
//#import "ZaynView.hpp"

@implementation AppDelegate



- (void)applicationDidFinishLaunching:(NSNotification *)notification {
        
    setupWindow();
    setupMetal();
    InitTriangle();
    InitializeGame();
//    UpdateGame();
    //[self performSelectorOnMainThread:@selector(startRenderLoop) withObject:nil waitUntilDone:NO];
//        [self gameLoop];
    [self performSelectorInBackground:@selector(startGameLoop) withObject:nil];
//    [self startGameLoop];
    
}



- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    CleanUpZayn();
    return YES;
}

- (void)startGameLoop {
    isRunning = YES;
    
    while (isRunning)
    {
        @autoreleasepool {
            if (zaynView)
            {
//                [zaynView pollEvents];
                // Call Poll for Input in NSView for NSEvents
            }
            UpdateGame();
            Render();
        }
//        Render();
      //  [self performSelector:@selector(startRenderLoop) withObject:nil afterDelay:(1.0 / 60.0)]; // 60 FPS
            
    }
   // UpdateGame();
    
}

@end
