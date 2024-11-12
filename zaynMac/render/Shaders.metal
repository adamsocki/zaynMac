//
//  Shaders.metal
//  zaynMac
//
//  Created by socki on 11/12/24.
//

#include <metal_stdlib>
#include <simd/simd.h>
using namespace metal;


struct VertexIn {
    vector_float2 position [[attribute(0)]];
    vector_float4 color [[attribute(1)]];
};

struct VertexOut {
    vector_float4 position [[position]];
    vector_float4 color;
};

vertex VertexOut vertex_main(VertexIn in [[stage_in]]) {
    VertexOut out;
    out.position = float4(in.position, 0.0, 1.0); // Corrected to add a comma between 0.0 and 1.0
    out.color = in.color;
    return out;
}

fragment float4 fragment_main(VertexOut in [[stage_in]]) {
    return in.color;
}
