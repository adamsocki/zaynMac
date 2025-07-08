#include "game_logic.hpp"
#include "math/math.h"
#include "input.hpp"
#include "camera.hpp"
#include "constants.h"
#include "zayn.hpp"

// Include game mode headers (legacy system)
#include "game_modes/cube_demo.hpp"
#include "game_modes/city_builder.hpp"
#include "game_modes/lighting_test.hpp"

// Include game project headers (new modular system) - conditional compilation
#include "game_projects/game_project_interface.hpp"


#if GAME_PROJECT_PLATFORMER
#include "game_projects/platformer_impl.hpp"
#endif

#if GAME_PROJECT_RPG

#endif
//#include "game_projects/rpg_impl.hpp"
//#elif GAME_PROJECT_PUZZLE
//    #include "game_projects/puzzle_impl.hpp"
//#elif ACTIVE_GAME_PROJECT == GAME_PROJECT_SHOOTER
//    #include "game_projects/shooter_impl.hpp"
//#elif ACTIVE_GAME_PROJECT == GAME_PROJECT_STRATEGY
//    #include "game_projects/strategy_impl.hpp"
//#else
//    #error "Unknown ACTIVE_GAME_PROJECT"


// Forward declare extern "C" functions
extern "C" {
    void UpdateGame(ZaynMemory* zaynMem, float deltaTime);
    
    // Game project interface functions (defined in individual game project files)
    void GameInit(ZaynMemory* zaynMem);
    void GameUpdate(ZaynMemory* zaynMem, float deltaTime);
    void GameGetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void GameShutdown(ZaynMemory* zaynMem);
}

GameLogic::GameLogic(ZaynMemory* zaynMem)
    : _zaynMem(zaynMem)
{
    _renderData = {};
}

GameLogic::~GameLogic()
{
    // Cleanup if needed
}

void GameLogic::Update(float deltaTime)
{
    if (!_zaynMem) return;
    
    // Set delta time for casette system
    _zaynMem->deltaTime = deltaTime;
    
    // Handle input (common to all game modes)
    UpdateSystems(deltaTime);
    HandleInput();
    UpdateCamera(deltaTime);
    
    // Update active game mode
    UpdateGame(_zaynMem, deltaTime);
    
    // Calculate matrices for rendering (common to all game modes)
    CalculateCameraMatrices();
    ProcessInstanceData();
    
    // Call casette system update and render
    ZaynUpdateAndRender(_zaynMem);
    
    // Mark render data as updated
    _renderData.deltaTime = deltaTime;
    _renderData.instanceDataUpdated = true;
}

RenderData GameLogic::GetRenderData()
{
    return _renderData;
}

void GameLogic::HandleInput()
{
    InputUpdatePolling(_zaynMem);
}

void GameLogic::UpdateSystems(float deltaTime)
{
    // Update time system
    _zaynMem->time.deltaTime = deltaTime;
    _zaynMem->time.totalTime += deltaTime;
    _zaynMem->time.frameCount++;
}

void GameLogic::UpdateCamera(float deltaTime)
{
    CameraUpdateMovement(&_zaynMem->camera, _zaynMem, deltaTime);
    CameraUpdateTest(&_zaynMem->camera);
}

//void GameLogic::UpdateScene(float deltaTime)
//{
//    if (_zaynMem->currentScene) {
//        _zaynMem->currentScene->Update(deltaTime);
//    }
//}

//void GameLogic::UpdateCityBuilder(float deltaTime)
//{
//    ::UpdateCityBuilder(_zaynMem, deltaTime);
//}
//
//void GameLogic::UpdateSceneFromGrid()
//{
//    ::UpdateSceneFromGrid(_zaynMem);
//}

void GameLogic::CalculateCameraMatrices()
{
    // Create view matrix from camera position and orientation
    simd::float3 cameraPos = _zaynMem->camera.position;
    simd::float3 cameraTarget = cameraPos + _zaynMem->camera.forward;
    
    // Create look-at matrix
    simd::float3 zAxis = simd::normalize(cameraPos - cameraTarget); // Forward (towards camera)
    simd::float3 xAxis = simd::normalize(simd::cross(_zaynMem->camera.up, zAxis)); // Right
    simd::float3 yAxis = simd::cross(zAxis, xAxis); // Up
    
    _renderData.viewMatrix = simd::float4x4{
        simd::float4{xAxis.x, yAxis.x, zAxis.x, 0.0f},
        simd::float4{xAxis.y, yAxis.y, zAxis.y, 0.0f},
        simd::float4{xAxis.z, yAxis.z, zAxis.z, 0.0f},
        simd::float4{-simd::dot(xAxis, cameraPos), -simd::dot(yAxis, cameraPos), -simd::dot(zAxis, cameraPos), 1.0f}
    };
    
    // Update camera data in ZaynMemory
    if (_zaynMem->cameraData) {
        _zaynMem->cameraData->worldTransform = _renderData.viewMatrix;
        _zaynMem->cameraData->worldNormalTransform = math::discardTranslation(_renderData.viewMatrix);
    }
    
    // Store the same matrix as cameraMatrix (for backward compatibility)
    _renderData.cameraMatrix = _renderData.viewMatrix;
}

void GameLogic::ProcessInstanceData()
{
    // This method handles any instance data processing that was previously done in the renderer
    // The actual instance data preparation will be handled by the renderer using scene data
    // This is just a placeholder for any game-logic specific instance processing
}

// Game Mode Dispatcher Functions (extern "C" to avoid name mangling)
extern "C" {
    
    void InitializeGame(ZaynMemory* zaynMem) {
        GameInit(zaynMem);
    }
    
    void UpdateGame(ZaynMemory* zaynMem, float deltaTime) {
        GameUpdate(zaynMem, deltaTime);
    }
    
    void ShutdownGame(ZaynMemory* zaynMem) {
        GameShutdown(zaynMem);
    }
}
