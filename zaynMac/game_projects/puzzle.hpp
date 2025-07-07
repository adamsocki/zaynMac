#pragma once

#include "game_project_interface.hpp"
#include "../math/math.h"

// Puzzle Game Project
// Grid-based puzzle game with match-3 mechanics

struct PuzzlePiece {
    int type;        // 0-5 different piece types
    int color;       // Color ID
    bool marked;     // Marked for removal
    bool falling;    // Currently falling
    float fallSpeed;
    simd::float3 position;
    simd::float3 targetPosition;
};

struct PuzzleState {
    // Grid system
    int gridWidth;
    int gridHeight;
    PuzzlePiece grid[10][10];  // 10x10 grid max
    
    // Game state
    int score;
    int level;
    int moves;
    int targetScore;
    float moveTimer;
    bool gameWon;
    bool gameOver;
    
    // Input state
    int selectedX;
    int selectedY;
    bool pieceSelected;
    
    // Animation state
    bool animating;
    float animationTimer;
    int matchCount;
    
    // Visual state
    simd::float3 cameraPosition;
    float pieceSize;
    float gridSpacing;
    
    // Timing
    float gameTime;
    float lastMoveTime;
    
    // Flags
    bool initialized;
};

// Puzzle-specific functions
namespace Puzzle {
    void Initialize(ZaynMemory* zaynMem);
    void Update(ZaynMemory* zaynMem, float deltaTime);
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void Shutdown(ZaynMemory* zaynMem);
    
    // Internal functions
    PuzzleState* GetState(ZaynMemory* zaynMem);
    void InitializeGrid(PuzzleState* state);
    void UpdateInput(PuzzleState* state, ZaynMemory* zaynMem);
    void UpdateAnimations(PuzzleState* state, float deltaTime);
    void CheckMatches(PuzzleState* state);
    void RemoveMatches(PuzzleState* state);
    void DropPieces(PuzzleState* state);
    void FillEmptySpaces(PuzzleState* state);
    bool IsValidMove(PuzzleState* state, int x1, int y1, int x2, int y2);
    void SwapPieces(PuzzleState* state, int x1, int y1, int x2, int y2);
    int GetRandomPieceType();
}

// Game project implementation (automatically included when this project is active)
extern "C" {
    void GameInit(ZaynMemory* zaynMem) {
        Puzzle::Initialize(zaynMem);
    }
    
    void GameUpdate(ZaynMemory* zaynMem, float deltaTime) {
        Puzzle::Update(zaynMem, deltaTime);
    }
    
    void GameGetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        Puzzle::GetInstanceData(zaynMem, instances, maxInstances, instanceCount);
    }
    
    void GameShutdown(ZaynMemory* zaynMem) {
        Puzzle::Shutdown(zaynMem);
    }
}