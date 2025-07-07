#pragma once

#include "game_project_interface.hpp"
#include "../math/math.h"

// RPG Game Project
// Turn-based RPG with character stats and combat system

struct RPGCharacter {
    simd::float3 position;
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    int level;
    int experience;
    float moveSpeed;
    bool isPlayer;
};

struct RPGState {
    // Player character
    RPGCharacter player;
    
    // NPCs/Enemies
    int npcCount;
    RPGCharacter npcs[32];
    
    // Game state
    bool inCombat;
    int currentTarget;
    float turnTimer;
    bool playerTurn;
    
    // World state
    simd::float3 cameraPosition;
    float worldSize;
    
    // UI state
    bool showInventory;
    bool showStats;
    
    // Game progression
    int currentLevel;
    int gold;
    float gameTime;
    
    // Flags
    bool initialized;
};

// RPG-specific functions
namespace RPG {
    void Initialize(ZaynMemory* zaynMem);
    void Update(ZaynMemory* zaynMem, float deltaTime);
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void Shutdown(ZaynMemory* zaynMem);
    
    // Internal functions
    RPGState* GetState(ZaynMemory* zaynMem);
    void UpdatePlayer(RPGState* state, ZaynMemory* zaynMem, float deltaTime);
    void UpdateNPCs(RPGState* state, float deltaTime);
    void UpdateCombat(RPGState* state, float deltaTime);
    void HandlePlayerInput(RPGState* state, ZaynMemory* zaynMem);
    void InitializeCharacter(RPGCharacter* character, bool isPlayer);
    void GenerateNPCs(RPGState* state);
}

// Game project implementation (automatically included when this project is active)
extern "C" {
    void GameInit(ZaynMemory* zaynMem) {
        RPG::Initialize(zaynMem);
    }
    
    void GameUpdate(ZaynMemory* zaynMem, float deltaTime) {
        RPG::Update(zaynMem, deltaTime);
    }
    
    void GameGetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        RPG::GetInstanceData(zaynMem, instances, maxInstances, instanceCount);
    }
    
    void GameShutdown(ZaynMemory* zaynMem) {
        RPG::Shutdown(zaynMem);
    }
}