//
//  entity.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#ifndef entity_hpp
#define entity_hpp

#include <stdio.h>
#include "data_types.h"
#include "render/mesh.hpp"
#include "types.h"

struct Transform
{
    vec3 position;
    vec3 rotation;
    vec3 scale;
    
    inline Transform() : position(V3(0,0,0)), rotation(V3(0,0,0)), scale(V3(1,1,1)) {}
};

struct GameObject
{
    MeshData* mesh;
    Transform transform;
    vec4 color;
    bool active;
    
    inline GameObject() : mesh(nullptr), color(V4(1,1,1,1)), active(true) {}
};

struct InstanceData
{
    mat4 transform;
    mat3 normalTransform;
    vec4 color;
};

#endif /* entity_hpp */
