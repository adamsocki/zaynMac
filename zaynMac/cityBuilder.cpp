//
//  cityBuilder.cpp
//  zaynMac
//
//  City builder game logic
//

#include "zayn.hpp"
#include "grid.hpp"
#include "scene.hpp"

void UpdateCityBuilder(ZaynMemory* zaynMem, float deltaTime)
{
    if (!zaynMem || !zaynMem->cityGrid || !zaynMem->currentScene) return;
    
    GridSystem* grid = zaynMem->cityGrid;
    InputDevice* mouse = zaynMem->inputManager.mouse;
    
    if (mouse)
    {
        // Convert mouse screen position to world position
        // Note: For now using window size - in a real implementation we'd get this from the window
        float screenWidth = 1024.0f;
        float screenHeight = 1024.0f;
        
        // Convert global screen coordinates to window-relative coordinates
        // For now, assume mouse coordinates are already relative to window
        simd::float3 mouseWorldPos_simd = ScreenToWorldPosition(zaynMem, 
            mouse->mouseState.x, mouse->mouseState.y, 
            screenWidth, screenHeight);
        
        // Convert simd::float3 to vec3
        vec3 mouseWorldPos = V3(mouseWorldPos_simd.x, mouseWorldPos_simd.y, mouseWorldPos_simd.z);
        
        // Update grid with mouse position
        UpdateGrid(grid, mouseWorldPos);
        
        // Handle mouse clicks
        if (IsMouseButtonClicked(mouse, MouseButton_Left))
        {
            // Place a building on the clicked tile
            if (grid->hoveredX >= 0 && grid->hoveredY >= 0)
            {
                TileType newType = TileType_Residential; // Default building type
                
                // Cycle through building types based on current tile
                GridTile* tile = GetTile(grid, grid->hoveredX, grid->hoveredY);
                if (tile)
                {
                    switch (tile->type)
                    {
                        case TileType_Grass:       newType = TileType_Residential; break;
                        case TileType_Residential: newType = TileType_Commercial; break;
                        case TileType_Commercial:  newType = TileType_Industrial; break;
                        case TileType_Industrial:  newType = TileType_Road; break;
                        case TileType_Road:        newType = TileType_Park; break;
                        case TileType_Park:        newType = TileType_Grass; break;
                        default:                   newType = TileType_Grass; break;
                    }
                    
                    SetTileType(grid, grid->hoveredX, grid->hoveredY, newType);
                }
            }
        }
        
        if (IsMouseButtonClicked(mouse, MouseButton_Right))
        {
            // Right click to clear tile back to grass
            if (grid->hoveredX >= 0 && grid->hoveredY >= 0)
            {
                SetTileType(grid, grid->hoveredX, grid->hoveredY, TileType_Grass);
            }
        }
    }
}

void UpdateSceneFromGrid(ZaynMemory* zaynMem)
{
    if (!zaynMem || !zaynMem->cityGrid || !zaynMem->currentScene) return;
    
    GridSystem* grid = zaynMem->cityGrid;
    Scene* scene = zaynMem->currentScene;
    
    // Clear current scene objects (keep first few demo objects, replace grid ones)
    // For simplicity, we'll regenerate all objects
    scene->gameObjects.count = 0;
    
    // Generate a game object for each grid tile
    for (int32 y = 0; y < grid->height; y++)
    {
        for (int32 x = 0; x < grid->width; x++)
        {
            GridTile* tile = GetTile(grid, x, y);
            if (!tile) continue;
            
            GameObject* obj = scene->CreateGameObject();
            if (!obj) continue;
            
            // Set position
            vec3 worldPos = GridToWorldPosition(grid, x, y);
            obj->transform.position = worldPos;
            obj->transform.scale = V3(grid->tileSize * 0.9f, 0.1f, grid->tileSize * 0.9f); // Slightly smaller than tile for grid lines
            
            // Set color based on tile type and state
            obj->color = tile->color;
            
            // Highlight hovered tile
            if (tile->hovered)
            {
                obj->color = V4(obj->color.x + 0.3f, obj->color.y + 0.3f, obj->color.z + 0.3f, 1.0f);
            }
            
            // Highlight selected tile
            if (tile->selected)
            {
                obj->color = V4(1.0f, 1.0f, 1.0f, 1.0f); // White selection
            }
            
            obj->active = true;
        }
    }
}
