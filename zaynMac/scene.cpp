//
//  scene.cpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#include "scene.hpp"

GameObject* CreateCube(Scene* scene, vec3 position, vec3 scale, vec4 color)
{
    GameObject* obj = scene->CreateGameObject();
    obj->transform.position = position;
    obj->transform.scale = scale;
    obj->color = color;
    return obj;
}

GameObject* CreateSphere(Scene* scene, vec3 position, float radius, vec4 color)
{
    GameObject* obj = scene->CreateGameObject();
    obj->transform.position = position;
    obj->transform.scale = V3(radius, radius, radius);
    obj->color = color;
    return obj;
}

void CreateSimpleScene(Scene* scene)
{
    // Create a few basic objects for a simple scene
    
    // Ground plane (scaled cube)
   // CreateCube(scene, V3(0, -1, 0), V3(10, 0.1f, 10), V4(0.5f, 0.8f, 0.3f, 1.0f));
    /*
    // Some cubes at different positions
    CreateCube(scene, V3(-2, 0, 0), V3(1, 1, 1), V4(1.0f, 0.2f, 0.2f, 1.0f));
    CreateCube(scene, V3(2, 0, 0), V3(1, 1, 1), V4(0.2f, 1.0f, 0.2f, 1.0f));
    CreateCube(scene, V3(0, 0, -2), V3(1, 1, 1), V4(0.2f, 0.2f, 1.0f, 1.0f));
    
    // A tall tower
    CreateCube(scene, V3(0, 2, 2), V3(0.5f, 3, 0.5f), V4(0.8f, 0.8f, 0.2f, 1.0f));
    
    // Some smaller objects
    CreateSphere(scene, V3(-1, 1, -1), 0.5f, V4(1.0f, 0.5f, 0.8f, 1.0f));
    CreateSphere(scene, V3(1, 1, 1), 0.3f, V4(0.5f, 1.0f, 1.0f, 1.0f));
     */
}
