
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
    [self performSelectorInBackground:@selector(startRenderLoop) withObject:nil];
    
}



- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

- (void)startRenderLoop {
    isRunning = YES;
    
    while (isRunning)
    {
        Render();
      //  [self performSelector:@selector(startRenderLoop) withObject:nil afterDelay:(1.0 / 60.0)]; // 60 FPS
            
    }
   // UpdateGame();
    
}

@end
