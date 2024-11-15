// AppDelegate.h
#import <Cocoa/Cocoa.h>

#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
//@interface AppDelegate : NSObject <NSApplicationDelegate>
//@property (strong, nonatomic) NSWindow *window;
//CVDisplayLinkRef displayLink;
//
//@end


@interface AppDelegate : NSObject <NSApplicationDelegate> {
    CVDisplayLinkRef displayLink;
    NSWindow *window;
    BOOL isRunning;
   // id<MTLDevice> device;
//    id<MTLCommandQueue> commandQueue;
//    id<MTLRenderPipelineState> pipelineState;
//    id<MTLBuffer> vertexBuffer;
   // CAMetalLayer *metalLayer;
}
- (void)startGameLoop;
@end
