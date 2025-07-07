# ZaynMac Lighting System Implementation Roadmap

## Overview
This document provides a comprehensive, phase-by-phase implementation guide for building an advanced lighting system in the ZaynMac game engine. Each phase builds upon the previous one, ensuring working results at every step while progressing toward advanced rendering techniques.

## Phase Dependencies
```
Phase 0 → Phase 1 → Phase 2 → Phase 3 → Phase 4
                      ↓         ↓         ↓
                  Phase 5 → Phase 6 → Phase 7
                      ↓         ↓         ↓
                  Phase 8 → Phase 9 → Phase 10
                      ↓         ↓         ↓
                  Phase 11 → Phase 12
```

---

## Phase 0: Texture Loading Foundation
**Objective**: Replace procedural textures with file-based texture loading
**Time Estimate**: 2-3 hours
**Visual Result**: Objects display loaded textures instead of procedural Mandelbrot pattern

### Implementation Details
- Create `Texture` struct with Metal texture wrapper
- Implement `TextureManager` with loading/caching
- Add `stb_image` for PNG/JPG loading
- Update shaders to support multiple texture slots

### Files to Create/Modify
- `zaynMac/render/texture.hpp` - Texture struct and functions
- `zaynMac/render/texture.cpp` - Texture loading implementation
- `zaynMac/render/renderer.hpp` - Add texture manager
- `zaynMac/render/renderer.cpp` - Update texture binding
- Shader code in `renderer.cpp` - Multiple texture support

### API Changes
```cpp
// New functions
int loadTexture(const char* path);
Texture* getTexture(int textureId);
void bindTexture(int textureId, int slot);
```

### Testing
- Load a simple texture (checker pattern or brick)
- Verify texture appears on cubes
- Check texture coordinates are correct
- Test multiple textures

### Assets Needed
- `assets/textures/test_texture.png` - Simple test texture
- `assets/textures/brick.png` - Brick texture
- `assets/textures/stone.png` - Stone texture

---

## Phase 1: Basic Multi-Light Support
**Objective**: Support multiple lights with different types
**Time Estimate**: 3-4 hours
**Visual Result**: Multiple colored lights affecting scene objects

### Implementation Details
- Create `Light` struct with position, color, type
- Implement `LightManager` with light array
- Add `LightData` uniform buffer (Buffer 4)
- Update fragment shader with multi-light loop

### Files to Create/Modify
- `zaynMac/render/lighting.hpp` - Light struct and manager
- `zaynMac/render/lighting.cpp` - Light management implementation
- `zaynMac/render/renderer.cpp` - Light buffer management
- Shader code - Multi-light fragment shader

### API Changes
```cpp
// New types
enum LightType { LIGHT_DIRECTIONAL, LIGHT_POINT, LIGHT_SPOT };

// New functions
int createLight(LightType type, simd::float3 position, simd::float3 color, float intensity);
void setLightPosition(int lightId, simd::float3 position);
void setLightColor(int lightId, simd::float3 color);
void setLightIntensity(int lightId, float intensity);
```

### Testing
- Create directional light (sun)
- Create point light (torch)
- Create spot light (flashlight)
- Verify lights combine properly
- Test light parameter changes

### Debug Checklist
- Lights appear in correct positions
- Light colors blend correctly
- Performance remains stable with multiple lights
- Light intensity changes are visible

---

## Phase 2: Enhanced Lighting Models (Phong/Blinn-Phong)
**Objective**: Add specular highlights and advanced lighting models
**Time Estimate**: 2-3 hours
**Visual Result**: Shiny surfaces with realistic highlights

### Implementation Details
- Extend `Material` struct with specular properties
- Add `MaterialData` uniform buffer (Buffer 3)
- Implement Phong and Blinn-Phong lighting models
- Add material property controls

### Files to Create/Modify
- `zaynMac/render/material.hpp` - Material struct and functions
- `zaynMac/render/material.cpp` - Material management
- `zaynMac/render/renderer.cpp` - Material buffer management
- Shader code - Phong/Blinn-Phong implementation

### API Changes
```cpp
// New struct
struct Material {
    simd::float3 diffuse;
    simd::float3 specular;
    float shininess;
    int diffuseTexture;
    int materialId;
};

// New functions
int createMaterial(simd::float3 diffuse, simd::float3 specular, float shininess);
int createMaterial(int textureId, simd::float3 diffuse, simd::float3 specular, float shininess);
void setMaterialProperty(int materialId, MaterialProperty prop, float value);
```

### Testing
- Create shiny metal material
- Create matte plastic material
- Test specular highlights from different angles
- Verify material parameter changes

---

## Phase 3: Normal Mapping
**Objective**: Add surface detail through normal maps
**Time Estimate**: 3-4 hours
**Visual Result**: Detailed surface bumps and indentations

### Implementation Details
- Extend texture system for normal maps
- Add tangent space calculations
- Implement normal map sampling in fragment shader
- Add tangent vectors to vertex data

### Files to Create/Modify
- `zaynMac/render/mesh.hpp` - Add tangent vectors
- `zaynMac/render/texture.hpp` - Normal map support
- Shader code - Tangent space normal mapping

### API Changes
```cpp
// Extended vertex data
struct VertexData {
    simd::float3 position;
    simd::float3 normal;
    simd::float3 tangent;
    simd::float3 bitangent;
    simd::float2 texcoord;
};

// New functions
void setMaterialNormalMap(int materialId, int normalMapId);
```

### Testing
- Load brick texture with normal map
- Verify surface detail appears
- Test normal mapping with different lights
- Check tangent space calculations

### Assets Needed
- `assets/textures/brick_normal.png` - Brick normal map
- `assets/textures/stone_normal.png` - Stone normal map

---

## Phase 4: Shadow Mapping
**Objective**: Add realistic shadows from lights
**Time Estimate**: 4-5 hours
**Visual Result**: Dynamic shadows cast by objects

### Implementation Details
- Implement shadow map generation
- Add depth render pass
- Implement shadow sampling in fragment shader
- Add shadow bias and PCF filtering

### Files to Create/Modify
- `zaynMac/render/shadow.hpp` - Shadow system
- `zaynMac/render/shadow.cpp` - Shadow map generation
- `zaynMac/render/renderer.cpp` - Shadow render pass
- Shader code - Shadow mapping shaders

### API Changes
```cpp
// New functions
void enableShadows(int lightId, int shadowMapSize);
void setShadowBias(int lightId, float bias);
void setShadowPCF(int lightId, bool enablePCF);
```

### Testing
- Enable shadows for directional light
- Verify shadows appear correctly
- Test shadow bias adjustment
- Check shadow filtering quality

---

## Phase 5: PBR Materials
**Objective**: Implement physically-based rendering
**Time Estimate**: 5-6 hours
**Visual Result**: Realistic metal and non-metal surfaces

### Implementation Details
- Extend material system for PBR properties
- Implement Cook-Torrance BRDF
- Add metallic/roughness workflow
- Support for environment reflections

### Files to Create/Modify
- `zaynMac/render/material.hpp` - PBR material properties
- Shader code - PBR BRDF implementation

### API Changes
```cpp
// PBR material properties
struct PBRMaterial {
    simd::float3 albedo;
    float metallic;
    float roughness;
    float ao;
    int albedoTexture;
    int metallicTexture;
    int roughnessTexture;
    int aoTexture;
};

// New functions
int createPBRMaterial(simd::float3 albedo, float metallic, float roughness);
void setPBRTextures(int materialId, int albedo, int metallic, int roughness, int ao);
```

### Testing
- Create metallic materials (gold, silver)
- Create dielectric materials (plastic, ceramic)
- Test roughness variations
- Verify energy conservation

---

## Phase 6: Image-Based Lighting (IBL)
**Objective**: Add environment-based lighting
**Time Estimate**: 4-5 hours
**Visual Result**: Realistic environment reflections and ambient lighting

### Implementation Details
- Load HDR environment maps
- Generate irradiance and prefiltered maps
- Implement environment BRDF lookup
- Add skybox rendering

### Files to Create/Modify
- `zaynMac/render/environment.hpp` - IBL system
- `zaynMac/render/environment.cpp` - Environment map processing
- Shader code - IBL implementation

### API Changes
```cpp
// New functions
int loadEnvironmentMap(const char* hdrPath);
void setEnvironmentMap(int envMapId);
void setEnvironmentIntensity(float intensity);
```

### Testing
- Load HDR environment map
- Verify environment reflections on metals
- Test diffuse environment lighting
- Check skybox rendering

### Assets Needed
- `assets/environments/studio.hdr` - HDR environment map

---

## Phase 7: Deferred Rendering
**Objective**: Support complex lighting scenarios efficiently
**Time Estimate**: 6-7 hours
**Visual Result**: Support for many lights without performance loss

### Implementation Details
- Implement G-buffer layout
- Add geometry pass rendering
- Implement lighting pass
- Add light culling optimization

### Files to Create/Modify
- `zaynMac/render/deferred.hpp` - Deferred rendering system
- `zaynMac/render/deferred.cpp` - Deferred implementation
- Shader code - G-buffer and lighting pass shaders

### API Changes
```cpp
// New functions
void enableDeferredRendering(bool enable);
void setGBufferDebug(GBufferTarget target);
```

### Testing
- Enable deferred rendering
- Test with many lights (100+)
- Verify G-buffer contents
- Check performance improvement

---

## Phase 8: Post-Processing Pipeline
**Objective**: Add HDR, bloom, and tone mapping
**Time Estimate**: 4-5 hours
**Visual Result**: Enhanced visual quality with bloom and tone mapping

### Implementation Details
- Implement HDR render targets
- Add bloom post-processing
- Implement tone mapping operators
- Add gamma correction

### Files to Create/Modify
- `zaynMac/render/postprocess.hpp` - Post-processing system
- `zaynMac/render/postprocess.cpp` - Post-processing implementation
- Shader code - Post-processing shaders

### API Changes
```cpp
// New functions
void enableHDR(bool enable);
void enableBloom(bool enable);
void setToneMapping(ToneMappingType type);
void setBloomThreshold(float threshold);
```

### Testing
- Enable HDR rendering
- Test bloom with bright lights
- Try different tone mapping operators
- Verify gamma correction

---

## Phase 9: Advanced Shadows (CSM, PCF)
**Objective**: Improve shadow quality and coverage
**Time Estimate**: 5-6 hours
**Visual Result**: High-quality shadows over large distances

### Implementation Details
- Implement cascaded shadow maps
- Add percentage-closer filtering
- Implement variance shadow maps
- Add shadow debugging tools

### Files to Create/Modify
- `zaynMac/render/shadow.hpp` - Advanced shadow techniques
- Shader code - Advanced shadow filtering

### API Changes
```cpp
// New functions
void enableCSM(int lightId, int cascadeCount);
void setShadowFiltering(ShadowFilterType type);
void setShadowDebug(bool enable);
```

### Testing
- Enable cascaded shadows
- Test shadow quality at different distances
- Verify filtering reduces aliasing
- Check performance impact

---

## Phase 10: Screen-Space Ambient Occlusion
**Objective**: Add realistic ambient occlusion
**Time Estimate**: 4-5 hours
**Visual Result**: Enhanced depth perception and contact shadows

### Implementation Details
- Implement SSAO algorithm
- Add temporal filtering
- Implement HBAO+ optimization
- Add SSAO debugging

### Files to Create/Modify
- `zaynMac/render/ssao.hpp` - SSAO system
- `zaynMac/render/ssao.cpp` - SSAO implementation
- Shader code - SSAO shaders

### API Changes
```cpp
// New functions
void enableSSAO(bool enable);
void setSSAORadius(float radius);
void setSSAOIntensity(float intensity);
```

### Testing
- Enable SSAO
- Test in complex geometry
- Adjust radius and intensity
- Check performance impact

---

## Phase 11: Advanced Materials (Parallax, Emission)
**Objective**: Add advanced material features
**Time Estimate**: 3-4 hours
**Visual Result**: Detailed surface displacement and glowing materials

### Implementation Details
- Implement parallax occlusion mapping
- Add emission mapping
- Implement material blending
- Add material debugging tools

### Files to Create/Modify
- `zaynMac/render/material.hpp` - Advanced material features
- Shader code - Advanced material shaders

### API Changes
```cpp
// New functions
void setMaterialParallax(int materialId, int heightMapId, float scale);
void setMaterialEmission(int materialId, int emissionMapId, float intensity);
```

### Testing
- Test parallax mapping on surfaces
- Create glowing materials
- Verify material blending
- Check debugging tools

---

## Phase 12: Performance Optimization
**Objective**: Optimize rendering performance
**Time Estimate**: 4-5 hours
**Visual Result**: Smooth performance with all features enabled

### Implementation Details
- Implement frustum culling
- Add level-of-detail system
- Optimize buffer management
- Add performance profiling

### Files to Create/Modify
- `zaynMac/render/culling.hpp` - Culling system
- `zaynMac/render/profiler.hpp` - Performance profiling
- All render files - Optimization passes

### API Changes
```cpp
// New functions
void enableFrustumCulling(bool enable);
void setLODDistance(float distance);
void enableProfiling(bool enable);
```

### Testing
- Test with large scenes
- Verify culling works correctly
- Check LOD transitions
- Profile performance bottlenecks

---

## Complete API Reference

### Texture System
```cpp
int loadTexture(const char* path);
int loadHDRTexture(const char* path);
Texture* getTexture(int textureId);
void bindTexture(int textureId, int slot);
```

### Material System
```cpp
int createMaterial(simd::float3 diffuse, simd::float3 specular, float shininess);
int createPBRMaterial(simd::float3 albedo, float metallic, float roughness);
void setMaterialProperty(int materialId, MaterialProperty prop, float value);
void setMaterialTexture(int materialId, TextureSlot slot, int textureId);
```

### Lighting System
```cpp
int createLight(LightType type, simd::float3 position, simd::float3 color, float intensity);
void setLightPosition(int lightId, simd::float3 position);
void setLightColor(int lightId, simd::float3 color);
void setLightIntensity(int lightId, float intensity);
void enableShadows(int lightId, int shadowMapSize);
```

### Environment System
```cpp
int loadEnvironmentMap(const char* hdrPath);
void setEnvironmentMap(int envMapId);
void setEnvironmentIntensity(float intensity);
```

### Post-Processing System
```cpp
void enableHDR(bool enable);
void enableBloom(bool enable);
void setToneMapping(ToneMappingType type);
void enableSSAO(bool enable);
```

### Debug System
```cpp
void setRenderDebug(DebugMode mode);
void enableProfiling(bool enable);
void setGBufferDebug(GBufferTarget target);
```

---

## Asset Requirements

### Phase 0-3 Assets
- `assets/textures/test_texture.png`
- `assets/textures/brick.png`
- `assets/textures/brick_normal.png`
- `assets/textures/stone.png`
- `assets/textures/stone_normal.png`

### Phase 5-6 Assets
- `assets/textures/metal_albedo.png`
- `assets/textures/metal_metallic.png`
- `assets/textures/metal_roughness.png`
- `assets/environments/studio.hdr`

### Phase 11 Assets
- `assets/textures/brick_height.png`
- `assets/textures/emission_map.png`

---

## Common Issues and Solutions

### Phase 0 Issues
- **Texture not loading**: Check file path and stb_image integration
- **Texture appears black**: Verify texture format and Metal texture creation
- **Texture coordinates wrong**: Check UV mapping in vertex data

### Phase 1 Issues
- **Lights not visible**: Check light buffer binding and shader uniforms
- **Light colors wrong**: Verify color space and gamma correction
- **Performance drop**: Check light count and shader complexity

### Phase 2 Issues
- **No specular highlights**: Check camera position and light direction
- **Specular too bright**: Adjust shininess and specular color
- **Material not changing**: Verify material buffer updates

### Phase 4 Issues
- **Shadow acne**: Adjust shadow bias
- **Peter panning**: Reduce shadow bias
- **Jagged shadows**: Increase shadow map resolution or add PCF

### Phase 5 Issues
- **Materials too dark**: Check energy conservation in BRDF
- **Metals not metallic**: Verify metallic texture and values
- **Roughness not working**: Check roughness texture and calculations

---

## Performance Expectations

### Phase 0-1: Baseline
- **GPU**: 60 FPS at 1920x1080
- **Memory**: +50MB for textures

### Phase 2-3: Enhanced
- **GPU**: 55 FPS at 1920x1080
- **Memory**: +100MB for materials

### Phase 4-5: Advanced
- **GPU**: 45 FPS at 1920x1080
- **Memory**: +200MB for shadows/PBR

### Phase 6-7: Complex
- **GPU**: 35 FPS at 1920x1080
- **Memory**: +300MB for IBL/deferred

### Phase 8-12: Optimized
- **GPU**: 60 FPS at 1920x1080 (with optimizations)
- **Memory**: Managed through LOD and culling

---

## Next Steps

1. **Start with Phase 0**: Build texture loading foundation
2. **Test Each Phase**: Verify visual results before moving on
3. **Create Test Scenes**: Build test scenes for each phase
4. **Profile Performance**: Monitor performance at each stage
5. **Build Asset Pipeline**: Create tools for content creation
6. **Document Progress**: Keep notes on what works and what doesn't

This roadmap provides a comprehensive path from basic texture loading to advanced rendering techniques, with each phase building upon the previous one while delivering visible results.