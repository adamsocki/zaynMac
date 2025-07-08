#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
//#include "../zayn.hpp"
#include "../camera.hpp"
#include "texture.hpp"

#include <simd/simd.h>


#include "constants.h"



class Renderer
{
    public:
        Renderer( MTL::Device* pDevice );
    ZaynMemory* zaynMem;
        ~Renderer();
        void buildShaders();
        void buildComputePipeline();
        void buildDepthStencilStates();
        void buildTextures();
        void buildBuffers();
        void generateMandelbrotTexture( MTL::CommandBuffer* pCommandBuffer );
        void draw( MTK::View* pView );
        
        // Texture management functions
        int loadTexture(const char* path);
        Texture* getTexture(int textureId);

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
        TextureManager _textureManager;
        float _angle;
        int _frame;
        dispatch_semaphore_t _semaphore;
        static const int kMaxFramesInFlight;
        uint _animationIndex;
};

