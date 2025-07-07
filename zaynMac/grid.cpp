//
//  grid.cpp
//  zaynMac
//
//  Grid system implementation for city builder game
//

#include "grid.hpp"
#include <string.h>

void InitializeGrid(GridSystem* grid, MemoryArena* arena, int32 width, int32 height, real32 tileSize)
{
    grid->width = width;
    grid->height = height;
    grid->tileSize = tileSize;
    grid->arena = arena;
    grid->worldPosition = V3(-width * tileSize * 0.5f, 0.0f, -height * tileSize * 0.5f);  // Center the grid
    
    // Allocate tiles
    size_t tileArraySize = width * height * sizeof(GridTile);
    grid->tiles = (GridTile*)AllocateMem(arena, tileArraySize);
    
    // Initialize tiles with default grass
    for (int32 y = 0; y < height; y++)
    {
        for (int32 x = 0; x < width; x++)
        {
            GridTile* tile = GetTile(grid, x, y);
            *tile = GridTile(); // Use default constructor
            
            // Create some variety in the initial terrain
            if ((x + y) % 7 == 0)
            {
                tile->type = TileType_Water;
                tile->color = GetTileTypeColor(TileType_Water);
            }
            else if ((x * 3 + y * 2) % 11 == 0)
            {
                tile->type = TileType_Park;
                tile->color = GetTileTypeColor(TileType_Park);
            }
        }
    }
}

void UpdateGrid(GridSystem* grid, vec3 mouseWorldPos)
{
    // Clear previous hover state
    if (grid->hoveredX >= 0 && grid->hoveredY >= 0)
    {
        GridTile* prevHovered = GetTile(grid, grid->hoveredX, grid->hoveredY);
        if (prevHovered) prevHovered->hovered = false;
    }
    
    // Convert mouse world position to grid coordinates
    int32 newX, newY;
    if (WorldToGridPosition(grid, mouseWorldPos, &newX, &newY))
    {
        grid->hoveredX = newX;
        grid->hoveredY = newY;
        
        GridTile* tile = GetTile(grid, newX, newY);
        if (tile)
        {
            tile->hovered = true;
        }
    }
    else
    {
        grid->hoveredX = -1;
        grid->hoveredY = -1;
    }
}

GridTile* GetTile(GridSystem* grid, int32 x, int32 y)
{
    if (!IsValidGridPosition(grid, x, y))
        return nullptr;
    
    return &grid->tiles[y * grid->width + x];
}

bool IsValidGridPosition(GridSystem* grid, int32 x, int32 y)
{
    return (x >= 0 && x < grid->width && y >= 0 && y < grid->height);
}

void SetTileType(GridSystem* grid, int32 x, int32 y, TileType type)
{
    GridTile* tile = GetTile(grid, x, y);
    if (tile)
    {
        tile->type = type;
        tile->color = GetTileTypeColor(type);
    }
}

vec3 GridToWorldPosition(GridSystem* grid, int32 x, int32 y)
{
    vec3 worldPos;
    worldPos.x = grid->worldPosition.x + (x + 0.5f) * grid->tileSize;
    worldPos.y = grid->worldPosition.y;
    worldPos.z = grid->worldPosition.z + (y + 0.5f) * grid->tileSize;
    return worldPos;
}

bool WorldToGridPosition(GridSystem* grid, vec3 worldPos, int32* outX, int32* outY)
{
    // Convert world position back to grid coordinates
    real32 relativeX = worldPos.x - grid->worldPosition.x;
    real32 relativeZ = worldPos.z - grid->worldPosition.z;
    
    int32 gridX = (int32)(relativeX / grid->tileSize);
    int32 gridY = (int32)(relativeZ / grid->tileSize);
    
    if (IsValidGridPosition(grid, gridX, gridY))
    {
        *outX = gridX;
        *outY = gridY;
        return true;
    }
    
    return false;
}

vec4 GetTileTypeColor(TileType type)
{
    switch (type)
    {
        case TileType_Empty:      return V4(0.2f, 0.2f, 0.2f, 1.0f);  // Dark gray
        case TileType_Grass:      return V4(0.3f, 0.7f, 0.2f, 1.0f);  // Green
        case TileType_Water:      return V4(0.2f, 0.4f, 0.8f, 1.0f);  // Blue
        case TileType_Road:       return V4(0.4f, 0.4f, 0.4f, 1.0f);  // Gray
        case TileType_Residential: return V4(0.8f, 0.8f, 0.3f, 1.0f); // Yellow
        case TileType_Commercial: return V4(0.3f, 0.8f, 0.8f, 1.0f);  // Cyan
        case TileType_Industrial: return V4(0.8f, 0.4f, 0.2f, 1.0f);  // Orange
        case TileType_Park:       return V4(0.2f, 0.8f, 0.3f, 1.0f);  // Bright green
        default:                  return V4(1.0f, 0.0f, 1.0f, 1.0f);  // Magenta (error)
    }
}