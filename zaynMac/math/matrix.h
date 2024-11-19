//
//  matrix.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#ifndef matrix_h
#define matrix_h

#include <stdio.h>

#include <cmath>
#include "../data_types.h"
#include "vector.h"
#include "quaternion.h"

#define _copysign(x, y) copysign(x, y)


union mat2
{
    real32 data[4];
    vec2 columns[2];
    struct
    {
        real32 m00;
        real32 m10;
        real32 m01;
        real32 m11;
    };
};

union mat3 {
    real32 data[9];
    vec3 columns[3];
    struct {
        real32 m00;
        real32 m10;
        real32 m20;
        real32 m01;
        real32 m11;
        real32 m21;
        real32 m02;
        real32 m12;
        real32 m22;
    };
};

union mat4 {
    real32 data[16];
    vec4 columns[4];
    struct {
        real32 m00;
        real32 m10;
        real32 m20;
        real32 m30;
        real32 m01;
        real32 m11;
        real32 m21;
        real32 m31;
        real32 m02;
        real32 m12;
        real32 m22;
        real32 m32;
        real32 m03;
        real32 m13;
        real32 m23;
        real32 m33;
    };
};

inline mat2 Zero2()
{
    mat2 result = {};
    return result;
};

inline mat3 Zero3() {
    mat3 result = {};
    return result;
};

inline mat4 Zero4() {
    mat4 result = {};
    return result;
}

inline mat2 Identity2()
{
    mat2 result = { 1.0f, 0.0f,
                   0.0f, 1.0f };

    return result;
}

inline mat3 Identity3() {
    mat3 result = { 1.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 1.0f };

    return result;
}

inline mat4 Identity4() {
    mat4 result = { 1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

inline mat4 Transpose(mat4 m) {
    mat4 m_;
    m_.columns[0] = { m.columns[0][0], m.columns[1][0], m.columns[2][0], m.columns[3][0] };
    m_.columns[1] = { m.columns[0][1], m.columns[1][1], m.columns[2][1], m.columns[3][1] };
    m_.columns[2] = { m.columns[0][2], m.columns[1][2], m.columns[2][2], m.columns[3][2] };
    m_.columns[3] = { m.columns[0][3], m.columns[1][3], m.columns[2][3], m.columns[3][3] };

    return m_;
}

inline vec3 GetX(mat4 a) {
    vec3 result = a.columns[0].xyz;
    return result;
}

inline vec3 GetY(mat4 a) {
    vec3 result = a.columns[1].xyz;
    return result;
}

inline vec3 GetZ(mat4 a) {
    vec3 result = a.columns[2].xyz;
    return result;
}

inline vec3 GetTranslation(mat4 a) {
    vec3 result = a.columns[3].xyz;
    return result;
}

inline vec3 GetScale(mat4 m) {
    vec3 result;
    result.x = Length(m.columns[0].xyz);
    result.y = Length(m.columns[1].xyz);
    result.z = Length(m.columns[2].xyz);

    return result;
}

inline mat3 GetRotation(mat4 m) {
    vec3 scale = GetScale(m);

    mat3 r;
#if 0
    r.m00 = m.m00 / scale.x;
    r.m10 = m.m10 / scale.x;
    r.m20 = m.m20 / scale.x;

    r.m01 = m.m01 / scale.y;
    r.m11 = m.m11 / scale.y;
    r.m21 = m.m21 / scale.y;

    r.m02 = m.m02 / scale.z;
    r.m12 = m.m12 / scale.z;
    r.m22 = m.m22 / scale.z;
#else
    r.columns[0][0] = m.columns[0][0] / scale.x;
    r.columns[0][1] = m.columns[0][1] / scale.x;
    r.columns[0][2] = m.columns[0][2] / scale.x;

    r.columns[1][0] = m.columns[1][0] / scale.x;
    r.columns[1][1] = m.columns[1][1] / scale.x;
    r.columns[1][2] = m.columns[1][2] / scale.x;

    r.columns[2][0] = m.columns[2][0] / scale.z;
    r.columns[2][1] = m.columns[2][1] / scale.z;
    r.columns[2][2] = m.columns[2][2] / scale.z;
#endif
    return r;
}

// https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
inline quaternion ToQuaternion(mat3 a) {
    quaternion result = {};

    result.w = sqrtf(Max(0.0f, 1.0f + a.columns[0][0] + a.columns[1][1] + a.columns[2][2])) / 2.0f;

    result.x = sqrtf(Max(0.0f, 1.0f + a.columns[0][0] - a.columns[1][1] - a.columns[2][2])) / 2.0f;
    result.y = sqrtf(Max(0.0f, 1.0f - a.columns[0][0] + a.columns[1][1] - a.columns[2][2])) / 2.0f;
    result.z = sqrtf(Max(0.0f, 1.0f - a.columns[0][0] - a.columns[1][1] + a.columns[2][2])) / 2.0f;

    // @NOTE: _copysign(x, y) returns a value with the magnitude of x and the sign of y
    result.x = _copysign(result.x, a.columns[2][1] - a.columns[1][2]);
    result.y = _copysign(result.y, a.columns[0][2] - a.columns[2][0]);
    result.z = _copysign(result.z, a.columns[1][0] - a.columns[0][1]);

    return result;
}
inline quaternion ToQuaternionFromMat4(mat4 a) {
    quaternion result = {};
    result.w = sqrtf(Max(0.0f, 1.0f + a.columns[0][0] + a.columns[1][1] + a.columns[2][2])) / 2.0f;

    result.x = sqrtf(Max(0.0f, 1.0f + a.columns[0][0] - a.columns[1][1] - a.columns[2][2])) / 2.0f;
    result.y = sqrtf(Max(0.0f, 1.0f - a.columns[0][0] + a.columns[1][1] - a.columns[2][2])) / 2.0f;
    result.z = sqrtf(Max(0.0f, 1.0f - a.columns[0][0] - a.columns[1][1] + a.columns[2][2])) / 2.0f;

    // @NOTE: _copysign(x, y) returns a value with the magnitude of x and the sign of y
    result.x = _copysign(result.x, a.columns[2][1] - a.columns[1][2]);
    result.y = _copysign(result.y, a.columns[0][2] - a.columns[2][0]);
    result.z = _copysign(result.z, a.columns[1][0] - a.columns[0][1]);
    return result;
}



inline vec3 GetX(mat3 a) {
    vec3 result = a.columns[0];
    return result;
}

inline vec3 GetY(mat3 a) {
    vec3 result = a.columns[1];
    return result;
}

inline vec3 GetZ(mat3 a) {
    vec3 result = a.columns[2];
    return result;
}


inline vec3 Row(mat3* a, int i) {
    vec3 result = V3(a->data[0 + i], a->data[3 + i], a->data[6 + i]);

    return result;
}

inline vec4 Row(mat4* a, int i) {
    vec4 result = V4(a->data[0 + i], a->data[4 + i], a->data[8 + i], a->data[12 + i]);

    return result;
}

inline void SwapRows(mat3* a, int i, int j) {
    vec3 oldRowI = Row(a, i);

    a->data[0 + i] = a->data[0 + j];
    a->data[3 + i] = a->data[3 + j];
    a->data[6 + i] = a->data[6 + j];

    a->data[0 + j] = oldRowI.data[0];
    a->data[3 + j] = oldRowI.data[1];
    a->data[6 + j] = oldRowI.data[2];
}

inline void SwapRows(mat4* a, int i, int j) {
    vec4 oldRowI = Row(a, i);

    a->data[0 + i] = a->data[0 + j];
    a->data[4 + i] = a->data[4 + j];
    a->data[8 + i] = a->data[8 + j];
    a->data[12 + i] = a->data[12 + j];

    a->data[0 + j] = oldRowI.data[0];
    a->data[4 + j] = oldRowI.data[1];
    a->data[8 + j] = oldRowI.data[2];
    a->data[12 + j] = oldRowI.data[3];
}

// rowI -> rowI + scale * rowJ
inline void AddRow(mat3* a, int i, int j, real32 scale) {
    a->data[0 + i] += scale * a->data[0 + j];
    a->data[3 + i] += scale * a->data[3 + j];
    a->data[6 + i] += scale * a->data[6 + j];
}

// rowI -> rowI + scale * rowJ
inline void AddRow(mat4* a, int i, int j, real32 scale) {
    a->data[0 + i] += scale * a->data[0 + j];
    a->data[4 + i] += scale * a->data[4 + j];
    a->data[8 + i] += scale * a->data[8 + j];
    a->data[12 + i] += scale * a->data[12 + j];
}

inline void MultiplyRow(mat3* a, int i, real32 scale) {
    a->data[0 + i] *= scale;
    a->data[3 + i] *= scale;
    a->data[6 + i] *= scale;
}

inline void MultiplyRow(mat4* a, int i, real32 scale) {
    a->data[0 + i] *= scale;
    a->data[4 + i] *= scale;
    a->data[8 + i] *= scale;
    a->data[12 + i] *= scale;
}

inline bool Inverse(mat3 a, mat3* inverted) {
    mat3 tmp = a;
    mat3 result = Identity3();

    for (int col = 0; col < 3; col++) {
        int maxRow = col;
        real32 maxRowValue = fabsf(tmp.data[3 * col + col]);

        for (int row = col + 1; row < 3; row++) {
            real32 rowValue = fabsf(tmp.data[3 * col + row]);

            if (rowValue > maxRowValue) {
                maxRow = row;
                maxRowValue = rowValue;
            }
        }

        SwapRows(&tmp, maxRow, col);
        SwapRows(&result, maxRow, col);

        float mJJ = tmp.data[3 * col + col];
        if (mJJ == 0) {
            return false;
        }

        MultiplyRow(&tmp, col, 1.0f / mJJ);
        MultiplyRow(&result, col, 1.0f / mJJ);

        for (int row = 0; row < 3; row++) {
            if (row == col) {
                continue;
            }

            float scale = -tmp.data[3 * col + row];
            AddRow(&tmp, row, col, scale);
            AddRow(&result, row, col, scale);
        }
    }

    if (inverted != NULL) {
        *inverted = result;
    }

    return true;
}

inline bool Inverse(mat4 a, mat4* inverted) {
    mat4 tmp = a;
    mat4 result = Identity4();

    for (int col = 0; col < 4; col++) {
        int maxRow = col;
        real32 maxRowValue = fabsf(tmp.data[4 * col + col]);

        for (int row = col + 1; row < 4; row++) {
            real32 rowValue = fabsf(tmp.data[4 * col + row]);

            if (rowValue > maxRowValue) {
                maxRow = row;
                maxRowValue = rowValue;
            }
        }

        SwapRows(&tmp, maxRow, col);
        SwapRows(&result, maxRow, col);

        float mJJ = tmp.data[4 * col + col];
        if (mJJ == 0) {
            return false;
        }

        MultiplyRow(&tmp, col, 1.0f / mJJ);
        MultiplyRow(&result, col, 1.0f / mJJ);

        for (int row = 0; row < 4; row++) {
            if (row == col) {
                continue;
            }

            float scale = -tmp.data[4 * col + row];
            AddRow(&tmp, row, col, scale);
            AddRow(&result, row, col, scale);
        }
    }

    if (inverted != NULL) {
        *inverted = result;
    }

    return true;
}

inline mat4 OrthogonalInverse(mat4 a) {

    vec3 X = a.columns[0].xyz;
    vec3 Y = a.columns[1].xyz;
    vec3 Z = a.columns[2].xyz;

    real32 invDet = 1.0f / Dot(Cross(X, Y), Z);

    vec3 row0 = Cross(Y, Z) * invDet;
    vec3 row1 = Cross(Z, X) * invDet;
    vec3 row2 = Cross(X, Y) * invDet;


    mat4 result;
    result.data[0] = row0[0];
    result.data[1] = row1[0];
    result.data[2] = row2[0];
    result.data[3] = 0.0f;

    result.data[4] = row0[1];
    result.data[5] = row1[1];
    result.data[6] = row2[1];
    result.data[7] = 0.0f;

    result.data[8] = row0[2];
    result.data[9] = row1[2];
    result.data[10] = row2[2];
    result.data[11] = 0.0f;

    result.data[12] = -(result.data[0] * a.data[12] + result.data[4] * a.data[13] + result.data[8] * a.data[14]);
    result.data[13] = -(result.data[1] * a.data[12] + result.data[5] * a.data[13] + result.data[9] * a.data[14]);
    result.data[14] = -(result.data[2] * a.data[12] + result.data[6] * a.data[13] + result.data[10] * a.data[14]);
    result.data[15] = 1.0f;

    return result;
}

inline mat2 operator*(mat2 a, mat2 b)
{
    mat2 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[2] * b.data[1];
    result.data[1] = a.data[1] * b.data[0] + a.data[3] * b.data[1];

    result.data[2] = a.data[0] * b.data[2] + a.data[2] * b.data[3];
    result.data[3] = a.data[1] * b.data[2] + a.data[3] * b.data[3];

    return result;
}


inline mat3 operator*(mat3 a, mat3 b) {
    mat3 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[3] * b.data[1] + a.data[6] + b.data[2];
    result.data[1] = a.data[1] * b.data[0] + a.data[4] * b.data[1] + a.data[7] + b.data[2];
    result.data[2] = a.data[2] * b.data[0] + a.data[5] * b.data[1] + a.data[8] + b.data[2];

    result.data[3] = a.data[0] * b.data[3] + a.data[3] * b.data[4] + a.data[6] + b.data[5];
    result.data[4] = a.data[1] * b.data[3] + a.data[4] * b.data[4] + a.data[7] + b.data[5];
    result.data[5] = a.data[2] * b.data[3] + a.data[5] * b.data[4] + a.data[8] + b.data[5];

    result.data[6] = a.data[0] * b.data[6] + a.data[3] * b.data[7] + a.data[6] + b.data[8];
    result.data[7] = a.data[1] * b.data[6] + a.data[4] * b.data[7] + a.data[7] + b.data[8];
    result.data[8] = a.data[2] * b.data[6] + a.data[5] * b.data[7] + a.data[8] + b.data[8];

    return result;
}

inline mat4 operator*(mat4 a, mat4 b) {
    mat4 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[4] * b.data[1] + a.data[8] * b.data[2] + a.data[12] * b.data[3];
    result.data[1] = a.data[1] * b.data[0] + a.data[5] * b.data[1] + a.data[9] * b.data[2] + a.data[13] * b.data[3];
    result.data[2] = a.data[2] * b.data[0] + a.data[6] * b.data[1] + a.data[10] * b.data[2] + a.data[14] * b.data[3];
    result.data[3] = a.data[3] * b.data[0] + a.data[7] * b.data[1] + a.data[11] * b.data[2] + a.data[15] * b.data[3];

    result.data[4] = a.data[0] * b.data[4] + a.data[4] * b.data[5] + a.data[8] * b.data[6] + a.data[12] * b.data[7];
    result.data[5] = a.data[1] * b.data[4] + a.data[5] * b.data[5] + a.data[9] * b.data[6] + a.data[13] * b.data[7];
    result.data[6] = a.data[2] * b.data[4] + a.data[6] * b.data[5] + a.data[10] * b.data[6] + a.data[14] * b.data[7];
    result.data[7] = a.data[3] * b.data[4] + a.data[7] * b.data[5] + a.data[11] * b.data[6] + a.data[15] * b.data[7];

    result.data[8] = a.data[0] * b.data[8] + a.data[4] * b.data[9] + a.data[8] * b.data[10] + a.data[12] * b.data[11];
    result.data[9] = a.data[1] * b.data[8] + a.data[5] * b.data[9] + a.data[9] * b.data[10] + a.data[13] * b.data[11];
    result.data[10] = a.data[2] * b.data[8] + a.data[6] * b.data[9] + a.data[10] * b.data[10] + a.data[14] * b.data[11];
    result.data[11] = a.data[3] * b.data[8] + a.data[7] * b.data[9] + a.data[11] * b.data[10] + a.data[15] * b.data[11];

    result.data[12] = a.data[0] * b.data[12] + a.data[4] * b.data[13] + a.data[8] * b.data[14] + a.data[12] * b.data[15];
    result.data[13] = a.data[1] * b.data[12] + a.data[5] * b.data[13] + a.data[9] * b.data[14] + a.data[13] * b.data[15];
    result.data[14] = a.data[2] * b.data[12] + a.data[6] * b.data[13] + a.data[10] * b.data[14] + a.data[14] * b.data[15];
    result.data[15] = a.data[3] * b.data[12] + a.data[7] * b.data[13] + a.data[11] * b.data[14] + a.data[15] * b.data[15];

    return result;
}

inline vec3 operator*(mat3 a, vec3 b) {
    vec3 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[3] * b.data[1] + a.data[6] * b.data[2];
    result.data[1] = a.data[1] * b.data[0] + a.data[4] * b.data[1] + a.data[7] * b.data[2];
    result.data[2] = a.data[2] * b.data[0] + a.data[5] * b.data[1] + a.data[8] * b.data[2];

    return result;
}

inline vec4 operator*(mat4 a, vec4 b) {
    vec4 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[4] * b.data[1] + a.data[8] * b.data[2] + a.data[12] * b.data[3];
    result.data[1] = a.data[1] * b.data[0] + a.data[5] * b.data[1] + a.data[9] * b.data[2] + a.data[13] * b.data[3];
    result.data[2] = a.data[2] * b.data[0] + a.data[6] * b.data[1] + a.data[10] * b.data[2] + a.data[14] * b.data[3];
    result.data[3] = a.data[3] * b.data[0] + a.data[7] * b.data[1] + a.data[11] * b.data[2] + a.data[15] * b.data[3];

    return result;
}

inline vec3 MultiplyDirection(mat4 a, vec3 b) {
    vec3 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[4] * b.data[1] + a.data[8] * b.data[2];
    result.data[1] = a.data[1] * b.data[0] + a.data[5] * b.data[1] + a.data[9] * b.data[2];
    result.data[2] = a.data[2] * b.data[0] + a.data[6] * b.data[1] + a.data[10] * b.data[2];

    result = Normalize(result);

    return result;
}

inline vec3 MultiplyPoint(mat4 a, vec3 b) {
    vec3 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[4] * b.data[1] + a.data[8] * b.data[2] + a.data[12];
    result.data[1] = a.data[1] * b.data[0] + a.data[5] * b.data[1] + a.data[9] * b.data[2] + a.data[13];
    result.data[2] = a.data[2] * b.data[0] + a.data[6] * b.data[1] + a.data[10] * b.data[2] + a.data[14];

    return result;
}

// Left multiplies by a row vector, resulting in a row vector
inline vec4 LeftMultiply(vec4 a, mat4 b) {
    vec4 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[1] * b.data[1] + a.data[2] * b.data[2] + a.data[3] * b.data[3];
    result.data[1] = a.data[0] * b.data[4] + a.data[1] * b.data[5] + a.data[2] * b.data[6] + a.data[3] * b.data[7];
    result.data[2] = a.data[0] * b.data[8] + a.data[1] * b.data[9] + a.data[2] * b.data[10] + a.data[3] * b.data[11];
    result.data[3] = a.data[0] * b.data[12] + a.data[1] * b.data[13] + a.data[2] * b.data[14] + a.data[3] * b.data[15];

    return result;
}

inline vec3 LeftMultiply(vec3 a, mat3 b) {
    vec3 result;

    result.data[0] = a.data[0] * b.data[0] + a.data[1] * b.data[1] + a.data[2] * b.data[2];
    result.data[1] = a.data[0] * b.data[3] + a.data[1] * b.data[4] + a.data[2] * b.data[5];
    result.data[2] = a.data[0] * b.data[6] + a.data[1] * b.data[7] + a.data[2] * b.data[8];

    return result;
}

inline vec3 ProjectPoint(mat4 a, vec3 b) {
    vec4 homogeneous = a * V4(b, 1.0f);
    vec3 result = homogeneous.xyz / homogeneous.w;
    return result;
}


// Constructors
inline mat4 Translation4(vec3 translation) {
    mat4 result = { 1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f,
                   translation.x, translation.y, translation.z, 1.0f };

    return result;
}

inline mat4 Rotation4(quaternion q) {
    mat4 result;

    result.columns[0] = V4(1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z,
        2.0f * (q.x * q.y + q.w * q.z),
        2.0f * (q.x * q.z - q.w * q.y),
        0.0f);
    result.columns[1] = V4(2.0f * (q.x * q.y - q.w * q.z),
        1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z,
        2.0f * (q.y * q.z + q.w * q.x),
        0.0f);
    result.columns[2] = V4(2.0f * (q.x * q.z + q.w * q.y),
        2.0f * (q.y * q.z - q.w * q.x),
        1.0f - 2.0f * (q.x * q.x + q.y * q.y),
        0.0f);
    result.columns[3] = V4(0.0f, 0.0f, 0.0f, 1.0f);

    return result;
}

inline mat4 Scale4(real32 scale) {
    mat4 result = { scale, 0.0f, 0.0f, 0.0f,
                   0.0f, scale, 0.0f, 0.0f,
                   0.0f, 0.0f, scale, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

inline mat4 Scale4(vec3 scale) {
    mat4 result = { scale.x, 0.0f, 0.0f, 0.0f,
                   0.0f, scale.y, 0.0f, 0.0f,
                   0.0f, 0.0f, scale.z, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

inline mat3 Translation3(vec3 translation) {
    mat3 result = { 1.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   translation.x, translation.y, 1.0f };

    return result;
}

inline mat3 Rotation3(quaternion q) {
    mat3 result;

    result.columns[0] = V3(1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z,
        2.0f * (q.x * q.y + q.w * q.z),
        2.0f * (q.x * q.z - q.w * q.y));
    result.columns[1] = V3(2.0f * (q.x * q.y - q.w * q.z),
        1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z,
        2.0f * (q.y * q.z + q.w * q.x));
    result.columns[2] = V3(2.0f * (q.x * q.z + q.w * q.y),
        2.0f * (q.y * q.z - q.w * q.x),
        1.0f - 2.0f * (q.x * q.x + q.y * q.y));

    return result;
}

inline mat3 Scale3(real32 scale) {
    mat3 result = { scale, 0.0f, 0.0f,
                   0.0f, scale, 0.0f,
                   0.0f, 0.0f, scale };

    return result;
}

inline mat3 Scale3(vec3 scale) {
    mat3 result = { scale.x, 0.0f, 0.0f,
                   0.0f, scale.y, 0.0f,
                   0.0f, 0.0f, scale.z };

    return result;
}

inline mat2 Scale2(real32 scale)
{
    mat2 result = { scale, 0.0f,
                   0.0f, scale };
    return result;
}

inline mat2 Scale2(vec2 scale) {
    mat2 result = { scale.x, 0.0f,
                   0.0f, scale.y, };

    return result;
}

inline mat4 TRS(vec3 translation, mat4 rotation, real32 scale) {
    mat4 result = rotation * Scale4(scale);

    result.columns[3].x = translation.x;
    result.columns[3].y = translation.y;
    result.columns[3].z = translation.z;

    return result;
}

inline mat4 TRS(vec3 translation, quaternion rotation, real32 scale) {
    mat4 result = Rotation4(rotation) * Scale4(scale);

    result.columns[3].x = translation.x;
    result.columns[3].y = translation.y;
    result.columns[3].z = translation.z;

    return result;
}

inline mat4 TRS(vec3 translation, quaternion rotation, vec3 scale) {
    mat4 result = Rotation4(rotation) * Scale4(scale);

    result.columns[3].x = translation.x;
    result.columns[3].y = translation.y;
    result.columns[3].z = translation.z;

    return result;
}

inline mat4 TS(vec3 translation, real32 scale) {
    mat4 result = Scale4(scale);

    result.columns[3].x = translation.x;
    result.columns[3].y = translation.y;
    result.columns[3].z = translation.z;

    return result;
}

inline mat4 TS(vec3 translation, vec3 scale) {
    mat4 result = Scale4(scale);

    result.columns[3].x = translation.x;
    result.columns[3].y = translation.y;
    result.columns[3].z = translation.z;

    return result;
}

inline mat4 TS(vec2 translation, vec2 scale) {
    mat4 result = Scale4(V3(scale, 1));

    result.columns[3].x = translation.x;
    result.columns[3].y = translation.y;

    return result;
}

inline mat4 RS(quaternion rotation, vec3 scale) {
    return Rotation4(rotation) * Scale4(scale);
}

inline mat4 Orthographic(real32 left, real32 right, real32 bottom, real32 top, real32 nearPlane, real32 farPlane) {
    mat4 result;

    result.columns[0] = V4(2.0f / (right - left), 0.0f, 0.0f, 0.0f);
    result.columns[1] = V4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f);
    result.columns[2] = V4(0.0f, 0.0f, -2.0f / (farPlane - nearPlane), 0.0f);
    result.columns[3] = V4(-(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        -(farPlane + nearPlane) / (farPlane - nearPlane),
        1.0f);

    return result;
}


// Points down +Z, with right-handed coordinate system
inline mat4 Perspective(real32 vFOV, real32 aspect, real32 nearDist, real32 farDist) {




    // return result;
    real32 tanHalfFov = tan(vFOV / 2.0f);

    mat4 result = {};

    result.m00 = 1.0f / (aspect * tanHalfFov);
    result.m11 = 1.0f / tanHalfFov;
    result.m22 = farDist / (farDist - nearDist);
    result.m23 = 1.0f;
    result.m32 = -(farDist * nearDist) / (farDist - nearDist);
    result.m33 = 0.0f;

    return result;
}



inline mat4 TranslateToMat4(vec3 vec, mat4 src)
{
    mat4 dest = Identity4();

    dest.m30 += src.m00 * vec.x + src.m10 * vec.y + src.m20 * vec.z;
    dest.m31 += src.m01 * vec.x + src.m11 * vec.y + src.m21 * vec.z;
    dest.m32 += src.m02 * vec.x + src.m12 * vec.y + src.m22 * vec.z;
    dest.m33 += src.m03 * vec.x + src.m13 * vec.y + src.m23 * vec.z;

    return dest;
}

inline mat4 matrixRotationTest(real32 angle, vec3 axis, mat4 src)
{
    mat4 dest = Identity4();

    real32 c = cosf(angle);
    real32 s = sinf(angle);

    real32 oneminusc = 1.0f - c;

    real32 xy = axis.x * axis.y;

    real32 yz = axis.y * axis.z;

    real32 xz = axis.x * axis.z;

    real32 xs = axis.x * s;

    real32 ys = axis.y * s;

    real32 zs = axis.z * s;

    real32 f00 = axis.x * axis.x * oneminusc + c;

    real32 f01 = xy * oneminusc + zs;

    real32 f02 = xz * oneminusc - ys;

    // n[3] not used

    real32 f10 = xy * oneminusc - zs;

    real32 f11 = axis.y * axis.y * oneminusc + c;

    real32 f12 = yz * oneminusc + xs;

    // n[7] not used

    real32 f20 = xz * oneminusc + ys;

    real32 f21 = yz * oneminusc - xs;

    real32 f22 = axis.z * axis.z * oneminusc + c;

    real32 t00 = src.m00 * f00 + src.m10 * f01 + src.m20 * f02;

    real32 t01 = src.m01 * f00 + src.m11 * f01 + src.m21 * f02;

    real32 t02 = src.m02 * f00 + src.m12 * f01 + src.m22 * f02;

    real32 t03 = src.m03 * f00 + src.m13 * f01 + src.m23 * f02;

    real32 t10 = src.m00 * f10 + src.m10 * f11 + src.m20 * f12;

    real32 t11 = src.m01 * f10 + src.m11 * f11 + src.m21 * f12;

    real32 t12 = src.m02 * f10 + src.m12 * f11 + src.m22 * f12;

    real32 t13 = src.m03 * f10 + src.m13 * f11 + src.m23 * f12;

    dest.m20 = src.m00 * f20 + src.m10 * f21 + src.m20 * f22;

    dest.m21 = src.m01 * f20 + src.m11 * f21 + src.m21 * f22;

    dest.m22 = src.m02 * f20 + src.m12 * f21 + src.m22 * f22;

    dest.m23 = src.m03 * f20 + src.m13 * f21 + src.m23 * f22;

    dest.m00 = t00;

    dest.m01 = t01;

    dest.m02 = t02;

    dest.m03 = t03;

    dest.m10 = t10;

    dest.m11 = t11;

    dest.m12 = t12;

    dest.m13 = t13;

    return dest;

}

inline mat4 PerspectiveInfiniteFarPlane(real32 vFOV, real32 aspect, real32 nearPlane) {
    real32 top = nearPlane * tanf(vFOV * 0.5f);
    real32 bottom = -top;

    real32 left = -aspect * top;
    real32 right = -left;

    mat4 result;

    result.columns[0] = V4(2 * nearPlane / (left - right), 0.0f, 0.0f, 0.0f);
    result.columns[1] = V4(0.0f, 2 * nearPlane / (top - bottom), 0.0f, 0.0f);
    result.columns[2] = V4(0.0f, 0.0f, 1.0f, 1.0f);
    result.columns[3] = V4(0.0f, 0.0f, -2.0f * nearPlane, 0.0f);

    return result;
}


inline mat4 lookAtv2(vec3 camPosition, vec3 lookAtPoint, vec3 upVector)
{
    mat4 returnMatrix = {};

    vec3 zaxis = Normalize(camPosition - lookAtPoint);
    vec3 xaxis = Normalize(Cross(upVector, zaxis));
    vec3 yaxis = Cross(zaxis, xaxis);

    mat4 translation = Translation4(camPosition);
    mat4 result = {};
    result.columns[0] = V4(xaxis.x, yaxis.x, zaxis.x, 0.0f);
    result.columns[1] = V4(xaxis.y, yaxis.y, zaxis.y, 0.0f);
    result.columns[2] = V4(xaxis.z, yaxis.z, zaxis.z, 0.0f);
    result.columns[3] = V4(0.0f, 0.0f, 0.0f, 1.0f);

    returnMatrix = result * translation;

    return returnMatrix;
}

inline real32 determinant3x3(real32 t00, real32 t01, real32 t02,
    real32 t10, real32 t11, real32 t12,
    real32 t20, real32 t21, real32 t22)
{
    return   t00 * (t11 * t22 - t12 * t21)
        + t01 * (t12 * t20 - t10 * t22)
        + t02 * (t10 * t21 - t11 * t20);
}

inline real32 determinantMat(mat4 matrix)
{
    real32 f = matrix.m00 * ((matrix.m11 * matrix.m22 * matrix.m33 + matrix.m12 * matrix.m23 * matrix.m31 + matrix.m13 * matrix.m21 * matrix.m32)
        - matrix.m13 * matrix.m22 * matrix.m31
        - matrix.m11 * matrix.m23 * matrix.m32
        - matrix.m12 * matrix.m21 * matrix.m33);
    f -= matrix.m01 * ((matrix.m10 * matrix.m22 * matrix.m33 + matrix.m12 * matrix.m23 * matrix.m30 + matrix.m13 * matrix.m20 * matrix.m32)
        - matrix.m13 * matrix.m22 * matrix.m30
        - matrix.m10 * matrix.m23 * matrix.m32
        - matrix.m12 * matrix.m20 * matrix.m33);
    f += matrix.m02 * ((matrix.m10 * matrix.m21 * matrix.m33 + matrix.m11 * matrix.m23 * matrix.m30 + matrix.m13 * matrix.m20 * matrix.m31)
        - matrix.m13 * matrix.m21 * matrix.m30
        - matrix.m10 * matrix.m23 * matrix.m31
        - matrix.m11 * matrix.m20 * matrix.m33);
    f -= matrix.m03 * ((matrix.m10 * matrix.m21 * matrix.m32 + matrix.m11 * matrix.m22 * matrix.m30 + matrix.m12 * matrix.m20 * matrix.m31)
        - matrix.m12 * matrix.m21 * matrix.m30
        - matrix.m10 * matrix.m22 * matrix.m31
        - matrix.m11 * matrix.m20 * matrix.m32);
    return f;
}

inline mat4 invert(mat4 src) {
    mat4 dest = {};
    real32 determinant = determinantMat(src);

    if (determinant != 0) {
        /*
         * m00 m01 m02 m03
         * m10 m11 m12 m13
         * m20 m21 m22 m23
         * m30 m31 m32 m33
         */
         // if (dest == NULL)
         //     dest = new Matrix4f();
        real32 determinant_inv = 1.0f / determinant;

        // first row
        real32 t00 = determinant3x3(src.m11, src.m12, src.m13, src.m21, src.m22, src.m23, src.m31, src.m32, src.m33);
        real32 t01 = -determinant3x3(src.m10, src.m12, src.m13, src.m20, src.m22, src.m23, src.m30, src.m32, src.m33);
        real32 t02 = determinant3x3(src.m10, src.m11, src.m13, src.m20, src.m21, src.m23, src.m30, src.m31, src.m33);
        real32 t03 = -determinant3x3(src.m10, src.m11, src.m12, src.m20, src.m21, src.m22, src.m30, src.m31, src.m32);
        // second row
        real32 t10 = -determinant3x3(src.m01, src.m02, src.m03, src.m21, src.m22, src.m23, src.m31, src.m32, src.m33);
        real32 t11 = determinant3x3(src.m00, src.m02, src.m03, src.m20, src.m22, src.m23, src.m30, src.m32, src.m33);
        real32 t12 = -determinant3x3(src.m00, src.m01, src.m03, src.m20, src.m21, src.m23, src.m30, src.m31, src.m33);
        real32 t13 = determinant3x3(src.m00, src.m01, src.m02, src.m20, src.m21, src.m22, src.m30, src.m31, src.m32);
        // third row
        real32 t20 = determinant3x3(src.m01, src.m02, src.m03, src.m11, src.m12, src.m13, src.m31, src.m32, src.m33);
        real32 t21 = -determinant3x3(src.m00, src.m02, src.m03, src.m10, src.m12, src.m13, src.m30, src.m32, src.m33);
        real32 t22 = determinant3x3(src.m00, src.m01, src.m03, src.m10, src.m11, src.m13, src.m30, src.m31, src.m33);
        real32 t23 = -determinant3x3(src.m00, src.m01, src.m02, src.m10, src.m11, src.m12, src.m30, src.m31, src.m32);
        // fourth row
        real32 t30 = -determinant3x3(src.m01, src.m02, src.m03, src.m11, src.m12, src.m13, src.m21, src.m22, src.m23);
        real32 t31 = determinant3x3(src.m00, src.m02, src.m03, src.m10, src.m12, src.m13, src.m20, src.m22, src.m23);
        real32 t32 = -determinant3x3(src.m00, src.m01, src.m03, src.m10, src.m11, src.m13, src.m20, src.m21, src.m23);
        real32 t33 = determinant3x3(src.m00, src.m01, src.m02, src.m10, src.m11, src.m12, src.m20, src.m21, src.m22);

        // transpose and divide by the determinant
        dest.m00 = t00 * determinant_inv;
        dest.m11 = t11 * determinant_inv;
        dest.m22 = t22 * determinant_inv;
        dest.m33 = t33 * determinant_inv;
        dest.m01 = t10 * determinant_inv;
        dest.m10 = t01 * determinant_inv;
        dest.m20 = t02 * determinant_inv;
        dest.m02 = t20 * determinant_inv;
        dest.m12 = t21 * determinant_inv;
        dest.m21 = t12 * determinant_inv;
        dest.m03 = t30 * determinant_inv;
        dest.m30 = t03 * determinant_inv;
        dest.m13 = t31 * determinant_inv;
        dest.m31 = t13 * determinant_inv;
        dest.m32 = t23 * determinant_inv;
        dest.m23 = t32 * determinant_inv;
        return dest;
    }
    // else
    //     return mat4 val = NULL;

    return dest;
}

mat4 SetViewDirection(vec3 position, vec3 direction, vec3 up);

mat4 SetViewTarget(vec3 position, vec3 target, vec3 up);

// void SetViewYXZ(glm::vec3 position, glm::vec3 rotation)
// {
//     const float c3 = glm::cos(rotation.z);
//     const float s3 = glm::sin(rotation.z);
//     const float c2 = glm::cos(rotation.x);
//     const float s2 = glm::sin(rotation.x);
//     const float c1 = glm::cos(rotation.y);
//     const float s1 = glm::sin(rotation.y);
//     const glm::vec3 u{(c1 * c3 + s1 * s2 * s3), (c2 * s3), (c1 * s2 * s3 - c3 * s1)};
//     const glm::vec3 v{(c3 * s1 * s2 - c1 * s3), (c2 * c3), (c1 * c3 * s2 + s1 * s3)};
//     const glm::vec3 w{(c2 * s1), (-s2), (c1 * c2)};
//     viewMatrix = glm::mat4{1.f};
//     viewMatrix[0][0] = u.x;
//     viewMatrix[1][0] = u.y;
//     viewMatrix[2][0] = u.z;
//     viewMatrix[0][1] = v.x;
//     viewMatrix[1][1] = v.y;
//     viewMatrix[2][1] = v.z;
//     viewMatrix[0][2] = w.x;
//     viewMatrix[1][2] = w.y;
//     viewMatrix[2][2] = w.z;
//     viewMatrix[3][0] = -glm::dot(u, position);
//     viewMatrix[3][1] = -glm::dot(v, position);
//     viewMatrix[3][2] = -glm::dot(w, position);
// }


inline vec4 transform(mat4 left, vec4 right) {

    vec4 dest = {};

    real32 x = left.m00 * right.x + left.m10 * right.y + left.m20 * right.z + left.m30 * right.w;
    real32 y = left.m01 * right.x + left.m11 * right.y + left.m21 * right.z + left.m31 * right.w;
    real32 z = left.m02 * right.x + left.m12 * right.y + left.m22 * right.z + left.m32 * right.w;
    real32 w = left.m03 * right.x + left.m13 * right.y + left.m23 * right.z + left.m33 * right.w;

    dest.x = x;
    dest.y = y;
    dest.z = z;
    dest.w = w;

    return dest;
}


inline mat4 LookAt(vec3 camPos, vec3 pt, vec3 Y) {

    vec3 forward = Normalize(camPos - pt);
    vec3 right = Normalize(Cross(Y, forward));
    vec3 up = Cross(forward, right);

    mat4 result = {};

#if 0
    result.columns[0][0] = right.x;
    result.columns[1][0] = right.y;
    result.columns[2][0] = right.z;

    result.columns[0][1] = up.x;
    result.columns[1][1] = up.y;
    result.columns[2][1] = up.z;

    result.columns[0][2] = forward.x;
    result.columns[1][2] = forward.y;
    result.columns[2][2] = forward.z;

    result.columns[0][3] = camPos.x;
    result.columns[1][3] = camPos.y;
    result.columns[2][3] = camPos.z;

#else
    result.columns[0][0] = right.x;
    result.columns[0][1] = right.y;
    result.columns[0][2] = right.z;

    result.columns[1][0] = up.x;
    result.columns[1][1] = up.y;
    result.columns[1][2] = up.z;

    result.columns[2][0] = forward.x;
    result.columns[2][1] = forward.y;
    result.columns[2][2] = forward.z;

    result.columns[3][0] = camPos.x;
    result.columns[3][1] = camPos.y;
    result.columns[3][2] = camPos.z;

    result.columns[3][3] = 1;
#endif
    return result;
}



#endif /* matrix_hpp */
