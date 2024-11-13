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

extern NSWindow *window;
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
//
//
//
#endif /* MetalSetup_h */
