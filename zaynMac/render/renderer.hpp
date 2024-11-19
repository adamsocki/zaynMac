#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include <simd/simd.h>

static constexpr size_t kMaxFramesInFlight = 3;
static constexpr size_t kInstanceRows = 10;
static constexpr size_t kInstanceColumns = 10;
static constexpr size_t kInstanceDepth = 10;
static constexpr uint32_t kTextureWidth = 128;
static constexpr uint32_t kTextureHeight = 128;

static constexpr size_t kNumInstances = (kInstanceRows * kInstanceColumns * kInstanceDepth);



class Renderer
{
    public:
        Renderer( MTL::Device* pDevice );
        ~Renderer();
        void buildShaders();
        void buildComputePipeline();
        void buildDepthStencilStates();
        void buildTextures();
        void buildBuffers();
        void generateMandelbrotTexture( MTL::CommandBuffer* pCommandBuffer );
        void draw( MTK::View* pView );

    private:
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCommandQueue;
        MTL::Library* _pShaderLibrary;
        MTL::RenderPipelineState* _pPSO;
        MTL::ComputePipelineState* _pComputePSO;
        MTL::DepthStencilState* _pDepthStencilState;
        MTL::Texture* _pTexture;
        MTL::Buffer* _pVertexDataBuffer;
        MTL::Buffer* _pInstanceDataBuffer[kMaxFramesInFlight];
        MTL::Buffer* _pCameraDataBuffer[kMaxFramesInFlight];
        MTL::Buffer* _pIndexBuffer;
        MTL::Buffer* _pTextureAnimationBuffer;
        float _angle;
        int _frame;
        dispatch_semaphore_t _semaphore;
        static const int kMaxFramesInFlight;
        uint _animationIndex;
};

