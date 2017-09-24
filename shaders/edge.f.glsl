// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Pawel Herman     - Added edge color.
// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.
// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

#version 430
#extension GL_ARB_shading_language_include : require

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} vertex_in;

in Triangle {
     flat vec4 edgeColor0;
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
     flat vec4 vertexColor0;
     flat vec4 vertexColor1;
     flat vec4 vertexColor2;
     flat vec3 maxheights;
} triangle_in;

layout(location = 5000) uniform float edgeWidth;
layout(location = 5001) uniform vec3 light;
layout(location = 5002) uniform vec4 modelColor;

out vec4 color;

#include "/happah/illumination.h.glsl"
#include "/happah/paint.h.glsl"

void main() {
     
     vec4 ec0 = triangle_in.edgeColor0;
     vec4 ec1 = triangle_in.edgeColor1;
     vec4 ec2 = triangle_in.edgeColor2;
     vec4 vc0 = triangle_in.vertexColor0;
     vec4 vc1 = triangle_in.vertexColor1;
     vec4 vc2 = triangle_in.vertexColor2;
     
     color = paint_edges(edgeWidth, vertex_in.dis, triangle_in.maxheights, modelColor, ec0, ec1, ec2, vc0, vc1, vc2);
     color = illuminate(light, vertex_in.normal.xyz, color);
}

