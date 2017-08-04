// Copyright 2017
// Distributed under the Boost Software License, Version 1.0.
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
 
// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.
// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

//TODO: range auf Pixel beziehen ~2 Pixel antialiasing

#version 430
#extension GL_ARB_shading_language_include : require

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} vertex_in;

layout(location = 5000) uniform vec4 edgeColor;
layout(location = 5001) uniform float edgeWidth;
layout(location = 5002) uniform vec3 light;
layout(location = 5003) uniform vec4 modelColor;

out vec4 color;

#include "/happah/illumination.h.glsl"
#include "/happah/paint.h.glsl"

void main() {
     
     color = paint_wf(edgeWidth, vertex_in.dis, modelColor, edgeColor);
     color = illuminate(light, vertex_in.normal.xyz, color);
}
