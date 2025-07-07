//
//  grid.hpp
//  zaynMac
//
//  Grid system for city builder game
//

#ifndef grid_hpp
#define grid_hpp

#include "entity.hpp"
#include "memory.hpp"

enum TileType
{
    TileType_Empty,
    TileType_Grass,
    TileType_Water,
    TileType_Road,
    TileType_Residential,
    TileType_Commercial,
    TileType_Industrial,
    TileType_Park,
    TileType_Count
};

struct GridTile
{
    TileType type;
    vec4 color;
    bool selected;
    bool hovered;
    int32 buildingID;    // ID of building placed on this tile (-1 if none)
    
    inline GridTile() : type(TileType_Grass), color(V4(0.3f, 0.7f, 0.2f, 1.0f)), 
                        selected(false), hovered(false), buildingID(-1) {}
};

struct GridSystem
{
    int32 width;
    int32 height;
    real32 tileSize;
    vec3 worldPosition;  // World position of grid origin (bottom-left)
    
    GridTile* tiles;     // 2D array stored as 1D: tiles[y * width + x]
    MemoryArena* arena;
    
    // Mouse interaction
    int32 hoveredX, hoveredY;
    int32 selectedX, selectedY;
    bool hasSelection;
    
    inline GridSystem() : width(0), height(0), tileSize(1.0f), 
                          worldPosition(V3(0,0,0)), tiles(nullptr), arena(nullptr),
                          hoveredX(-1), hoveredY(-1), selectedX(-1), selectedY(-1), 
                          hasSelection(false) {}
};

// Grid functions
void InitializeGrid(GridSystem* grid, MemoryArena* arena, int32 width, int32 height, real32 tileSize);
void UpdateGrid(GridSystem* grid, vec3 mouseWorldPos);
GridTile* GetTile(GridSystem* grid, int32 x, int32 y);
bool IsValidGridPosition(GridSystem* grid, int32 x, int32 y);
void SetTileType(GridSystem* grid, int32 x, int32 y, TileType type);
vec3 GridToWorldPosition(GridSystem* grid, int32 x, int32 y);
bool WorldToGridPosition(GridSystem* grid, vec3 worldPos, int32* outX, int32* outY);

// Get color for tile type
vec4 GetTileTypeColor(TileType type);

#endif /* grid_hpp */