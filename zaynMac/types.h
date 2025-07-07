//
//  types.h
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#pragma once

#include "data_types.h"

// Simple vector types
struct vec3 {
    real32 x, y, z;
};

struct vec4 {
    real32 x, y, z, w;
};

// Simple matrix types  
struct mat3 {
    real32 m00, m10, m20;
    real32 m01, m11, m21;
    real32 m02, m12, m22;
};

struct mat4 {
    real32 m00, m10, m20, m30;
    real32 m01, m11, m21, m31;
    real32 m02, m12, m22, m32;
    real32 m03, m13, m23, m33;
};

// Constructors
inline vec3 V3(real32 x, real32 y, real32 z) {
    vec3 result = {x, y, z};
    return result;
}

inline vec4 V4(real32 x, real32 y, real32 z, real32 w) {
    vec4 result = {x, y, z, w};
    return result;
}

inline mat3 Identity3() {
    mat3 result = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    return result;
}

inline mat4 Identity4() {
    mat4 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return result;
}
