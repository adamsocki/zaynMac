#include "texture.hpp"
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Texture class implementation
Texture::Texture() 
    : _metalTexture(nullptr), _width(0), _height(0), _channels(0), _isValid(false) {
}

Texture::~Texture() {
    release();
}

bool Texture::loadFromFile(const char* path, MTL::Device* device) {
    if (!path || !device) {
        printf("Texture::loadFromFile - Invalid parameters\n");
        return false;
    }
    
    printf("Attempting to load texture: %s\n", path);
    
    // Load image data using stb_image
    int width, height, channels;
    unsigned char* imageData = stbi_load(path, &width, &height, &channels, 4); // Force 4 channels (RGBA)
    
    if (!imageData) {
        printf("Failed to load texture: %s - Error: %s\n", path, stbi_failure_reason());
        return false;
    }
    
    printf("Successfully loaded texture: %s (%dx%d, %d channels)\n", path, width, height, channels);
    
    // Create Metal texture descriptor
    MTL::TextureDescriptor* textureDesc = MTL::TextureDescriptor::alloc()->init();
    textureDesc->setWidth(width);
    textureDesc->setHeight(height);
    textureDesc->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    textureDesc->setTextureType(MTL::TextureType2D);
    textureDesc->setStorageMode(MTL::StorageModeManaged);
    textureDesc->setUsage(MTL::ResourceUsageSample | MTL::ResourceUsageRead);
    
    // Create Metal texture
    MTL::Texture* metalTexture = device->newTexture(textureDesc);
    if (!metalTexture) {
        stbi_image_free(imageData);
        textureDesc->release();
        return false;
    }
    
    // Upload image data to texture
    MTL::Region region = MTL::Region::Make2D(0, 0, width, height);
    metalTexture->replaceRegion(region, 0, imageData, width * 4);
    
    // Fill texture properties
    _metalTexture = metalTexture;
    _width = width;
    _height = height;
    _channels = 4; // We forced RGBA
    _isValid = true;
    
    // Clean up
    stbi_image_free(imageData);
    textureDesc->release();
    
    return true;
}

void Texture::release() {
    if (_metalTexture) {
        _metalTexture->release();
        _metalTexture = nullptr;
        _isValid = false;
    }
}

// TextureManager class implementation
TextureManager::TextureManager(MTL::Device* device) 
    : _device(device), _nextTextureId(1) {
}

TextureManager::~TextureManager() {
    // Release all textures
    for (auto& pair : _textures) {
        delete pair.second;
    }
    _textures.clear();
    _pathToId.clear();
}

int TextureManager::loadTexture(const char* path) {
    if (!path) {
        printf("TextureManager::loadTexture - No path provided\n");
        return -1;
    }
    
    printf("TextureManager loading: %s\n", path);
    
    std::string pathStr(path);
    
    // Check if texture already loaded
    auto it = _pathToId.find(pathStr);
    if (it != _pathToId.end()) {
        printf("Texture already loaded with ID: %d\n", it->second);
        return it->second;
    }
    
    // Load new texture
    Texture* texture = new Texture();
    if (texture->loadFromFile(path, _device)) {
        int textureId = _nextTextureId++;
        _textures[textureId] = texture;
        _pathToId[pathStr] = textureId;
        printf("Texture loaded successfully with ID: %d\n", textureId);
        return textureId;
    }
    
    printf("Failed to load texture: %s\n", path);
    delete texture;
    return -1;
}

Texture* TextureManager::getTexture(int textureId) {
    auto it = _textures.find(textureId);
    if (it != _textures.end()) {
        return it->second;
    }
    return nullptr;
}

void TextureManager::bindTexture(int textureId, int slot) {
    // This function will be used by the renderer to bind textures
    // Implementation depends on how we integrate with the renderer
}