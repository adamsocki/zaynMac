#pragma once

#include <Metal/Metal.hpp>
#include <string>
#include <unordered_map>

class Texture {
public:
    Texture();
    ~Texture();
    
    bool loadFromFile(const char* path, MTL::Device* device);
    void release();
    
    MTL::Texture* getMetalTexture() const { return _metalTexture; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    int getChannels() const { return _channels; }
    bool isValid() const { return _isValid; }
    
private:
    MTL::Texture* _metalTexture;
    int _width;
    int _height;
    int _channels;
    bool _isValid;
};

class TextureManager {
public:
    TextureManager(MTL::Device* device);
    ~TextureManager();
    
    int loadTexture(const char* path);
    Texture* getTexture(int textureId);
    void bindTexture(int textureId, int slot);
    
private:
    MTL::Device* _device;
    std::unordered_map<int, Texture*> _textures;
    std::unordered_map<std::string, int> _pathToId;
    int _nextTextureId;
};