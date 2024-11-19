//
//  mesh.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include "../data_types.h"
#include <Metal/Metal.hpp>


// Mesh data structure
struct MeshData
{
    MTL::Buffer* vertexBuffer;
    MTL::Buffer* indexBuffer;
    int32 indexCount;
    int32 vertexCount;
};


#endif /* mesh_hpp */
