#pragma once

#include "zayn.hpp"
#include <simd/simd.h>

struct RenderData
{
    simd::float4x4 cameraMatrix;
    simd::float4x4 viewMatrix;
    simd::float4x4 projectionMatrix;
    bool instanceDataUpdated;
    float deltaTime;
};

class GameLogic
{
public:
    GameLogic(ZaynMemory* zaynMem);
    ~GameLogic();
    
    void Update(float deltaTime);
    RenderData GetRenderData();
    
    void HandleInput();
    void UpdateSystems(float deltaTime);
    void UpdateCamera(float deltaTime);
    void UpdateScene(float deltaTime);
    void UpdateCityBuilder(float deltaTime);
    void UpdateSceneFromGrid();
    
private:
    ZaynMemory* _zaynMem;
    RenderData _renderData;
    
    void CalculateCameraMatrices();
    void ProcessInstanceData();
};