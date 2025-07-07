//
//  scene.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#ifndef scene_hpp
#define scene_hpp

#include "entity.hpp"
#include "dynamic_array.hpp"
#include "memory.hpp"

struct Scene
{
    DynamicArray<GameObject> gameObjects;
    MemoryArena* arena;
    
    Scene(MemoryArena* memArena) : arena(memArena) 
    {
        gameObjects = MakeDynamicArray<GameObject>(arena, 100);
    }
    
    GameObject* CreateGameObject()
    {
        GameObject newObj;
        PushBack(&gameObjects, newObj);
        return &gameObjects[gameObjects.count - 1];
    }
    
    void Update(float deltaTime)
    {
        for (int i = 0; i < gameObjects.count; i++)
        {
            if (gameObjects[i].active)
            {
                // Update game object logic here
            }
        }
    }
    
    void GetInstanceData(InstanceData* instances, int maxInstances, int& instanceCount)
    {
        instanceCount = 0;
        for (int i = 0; i < gameObjects.count && instanceCount < maxInstances; i++)
        {
            GameObject& obj = gameObjects[i];
            if (obj.active)
            {
                // Create simple transform matrix from Transform data
                mat4 transform = Identity4();
                
                // Apply scale
                transform.m00 *= obj.transform.scale.x;
                transform.m11 *= obj.transform.scale.y;
                transform.m22 *= obj.transform.scale.z;
                
                // Apply translation
                transform.m03 = obj.transform.position.x;
                transform.m13 = obj.transform.position.y;
                transform.m23 = obj.transform.position.z;
                
                instances[instanceCount].transform = transform;
                
                // Create normal transform (just upper 3x3 for now)
                mat3 normalTransform = Identity3();
                normalTransform.m00 = transform.m00;
                normalTransform.m01 = transform.m01;
                normalTransform.m02 = transform.m02;
                normalTransform.m10 = transform.m10;
                normalTransform.m11 = transform.m11;
                normalTransform.m12 = transform.m12;
                normalTransform.m20 = transform.m20;
                normalTransform.m21 = transform.m21;
                normalTransform.m22 = transform.m22;
                
                instances[instanceCount].normalTransform = normalTransform;
                instances[instanceCount].color = obj.color;
                instanceCount++;
            }
        }
    }
};

#endif /* scene_hpp */