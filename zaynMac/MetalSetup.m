////
////  MetalSetup.m
////  zaynMac
////
////  Created by socki on 11/12/24.
////
//



//
//
//// MetalSetup.m
#import "MetalSetup.h"
#import "ZaynView.hpp"
//#import "MyView.h"
//
NSWindow *window;
id<MTLDevice> device;
id<MTLCommandQueue> commandQueue;
id<MTLRenderPipelineState> pipelineState;
id<MTLBuffer> vertexBuffer;
CAMetalLayer *metalLayer;
//
@implementation MetalSetup : NSObject

@end

void setupWindow() 
{
    // Create window
    NSRect frame = NSMakeRect(0, 0, 800, 600);
    window = [[NSWindow alloc] initWithContentRect:frame
                                          styleMask:(NSWindowStyleMaskTitled |
                                                     NSWindowStyleMaskClosable |
                                                     NSWindowStyleMaskResizable |
                                                     NSWindowStyleMaskMiniaturizable)
                                            backing:NSBackingStoreBuffered
                                              defer:NO];

    [window setTitle:@"Metal Hello World"];
    [window makeKeyAndOrderFront:nil];

    // Set up Metal layer
    metalLayer = [CAMetalLayer layer];
    metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalLayer.framebufferOnly = YES;
    metalLayer.frame = frame;
    metalLayer.displaySyncEnabled = YES; // Disable vsync
    
    // Create custom view and set as content view
    ZaynView *zaynView = [[ZaynView alloc] initWithFrame:frame];
    [zaynView setLayer:metalLayer];
    [zaynView setWantsLayer:YES];
    [window setContentView:zaynView];
    [window makeFirstResponder:zaynView];
}



void setupMetal() {
    // Create Metal device and command queue
    device = MTLCreateSystemDefaultDevice();
    commandQueue = [device newCommandQueue];
    metalLayer.device = device;
}

#import <simd/simd.h>

struct Vertex {
    vector_float2 position;
    vector_float4 color;
};

void InitTriangle() {
    struct Vertex triangleVertices[] = {
        { { 0.0f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },  // Top vertex (red)
        { { -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // Bottom left vertex (green)
        { { 0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }   // Bottom right vertex (blue)
    };

    vertexBuffer = [device newBufferWithBytes:triangleVertices
                                       length:sizeof(triangleVertices)
                                      options:MTLResourceStorageModeShared];

    NSError *error = nil;
    id<MTLLibrary> library = [device newDefaultLibrary];
    id<MTLFunction> vertexFunction = [library newFunctionWithName:@"vertex_main"];
    id<MTLFunction> fragmentFunction = [library newFunctionWithName:@"fragment_main"];

    // Set up vertex descriptor
    MTLVertexDescriptor *vertexDescriptor = [[MTLVertexDescriptor alloc] init];
    vertexDescriptor.attributes[0].format = MTLVertexFormatFloat2; // position
    vertexDescriptor.attributes[0].offset = offsetof(struct Vertex, position);
    vertexDescriptor.attributes[0].bufferIndex = 0;

    vertexDescriptor.attributes[1].format = MTLVertexFormatFloat4; // color
    vertexDescriptor.attributes[1].offset = offsetof(struct Vertex, color);
    vertexDescriptor.attributes[1].bufferIndex = 0;

    vertexDescriptor.layouts[0].stride = sizeof(struct Vertex);
    vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;

    // Create pipeline descriptor and assign the vertex descriptor
    MTLRenderPipelineDescriptor *pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDescriptor.vertexFunction = vertexFunction;
    pipelineDescriptor.fragmentFunction = fragmentFunction;
    pipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    pipelineDescriptor.vertexDescriptor = vertexDescriptor;

    pipelineState = [device newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];
    if (error) {
        NSLog(@"Error creating pipeline state: %@", error);
    }
}

void RenderTriangle() {
    NSLog(@"HHH");
    @autoreleasepool {
        id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
        if (!drawable) return;

        MTLRenderPassDescriptor *passDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
        passDescriptor.colorAttachments[0].texture = drawable.texture;
        passDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        passDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.2, 0.2, 0.2, 1.0);

        id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
        id<MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:passDescriptor];

        [encoder setRenderPipelineState:pipelineState];
        [encoder setVertexBuffer:vertexBuffer offset:0 atIndex:0];

        [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

        [encoder endEncoding];
        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
    }
}

void Render() {
    RenderTriangle();
}
//
//void InitializeGame() {
//    // Initialize your game state here
//}
//
//void UpdateGame() {
//    // Update your game state here
//}
