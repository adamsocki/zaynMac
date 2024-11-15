////
////  MetalSetup.h
////  zaynMac
////
////  Created by socki on 11/12/24.
////
//
#ifndef MetalSetup_h
#define MetalSetup_h
//
//// MetalSetup.h
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <simd/simd.h>
#import <Cocoa/Cocoa.h>
#import "ZaynView.hpp"

@interface MetalSetup : NSObject

// Declare any methods or properties here



extern NSWindow *window;
extern ZaynView *zaynView;
extern id<MTLDevice> device;
extern id<MTLCommandQueue> commandQueue;
extern id<MTLRenderPipelineState> pipelineState;
extern id<MTLBuffer> vertexBuffer;
extern CAMetalLayer *metalLayer;

void setupWindow();
void setupMetal();
//void InitializeGame();
//void UpdateGame();
void Render();
void InitTriangle();
void RenderTriangle();




@end
#endif /* MetalSetup_h */
