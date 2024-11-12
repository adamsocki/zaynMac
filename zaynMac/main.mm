
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION


#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>


#import "zayn.hpp"

#import <simd/simd.h>

NSApplication *app;
NSWindow *window;
id<MTLDevice> device;
id<MTLCommandQueue> commandQueue;
id<MTLRenderPipelineState> pipelineState;
id<MTLBuffer> vertexBuffer;
CAMetalLayer *metalLayer;

void setupWindow();
void setupMetal();
void render();
void runApp();
void InitTriangle();
void RenderTriangle();

int main() {
    setupWindow();
    setupMetal();
    InitializeGame();
    runApp();
    return 0;
}

void setupWindow() {
    // Initialize Cocoa application
    app = [NSApplication sharedApplication];
    
    // Create window
    NSRect frame = NSMakeRect(0, 0, 800, 600);
    window = [[NSWindow alloc] initWithContentRect:frame
                                          styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    [window setTitle:@"Metal Hello World"];
    [window makeKeyAndOrderFront:nil];
    
    // Set up Metal layer
    metalLayer = [CAMetalLayer layer];
    metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalLayer.framebufferOnly = YES;
    metalLayer.frame = frame;
//    metalLayer.displaySyncEnabled = NO;
    [window.contentView setLayer:metalLayer];
    [window.contentView setWantsLayer:YES];
}

void setupMetal() {
    // Create Metal device and command queue
    device = MTLCreateSystemDefaultDevice();
    commandQueue = [device newCommandQueue];
    metalLayer.device = device;
}

struct Vertex {
    vector_float2 position;
    vector_float4 color;
};

void InitTriangle() {
    

    Vertex triangleVertices[] = {
        { { 0.0f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },  // Top vertex (red)
        { { -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // Bottom left vertex (red)
        { { 0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }   // Bottom right vertex (red)
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
    vertexDescriptor.attributes[0].offset = 0;
    vertexDescriptor.attributes[0].bufferIndex = 0;

    vertexDescriptor.attributes[1].format = MTLVertexFormatFloat4; // color
    vertexDescriptor.attributes[1].offset = sizeof(vector_float4);
    vertexDescriptor.attributes[1].bufferIndex = 0;

    vertexDescriptor.layouts[0].stride = sizeof(Vertex);
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


void render() {
    @autoreleasepool {
        
        UpdateGame();
    }
}

void runApp() {
    // Main loop
    [app finishLaunching];
    while (![app isRunning]) {
        render();
        NSEvent *event = [app nextEventMatchingMask:NSEventMaskAny
                                           untilDate:nil
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES];
        [app sendEvent:event];
        [app updateWindows];
    }
}
