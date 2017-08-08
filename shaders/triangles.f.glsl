// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.07 - Hedwig Amberg    - add new shader for coloring triangles individualy.
// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

#version 430
#extension GL_ARB_shading_language_include : require

in Vertex {
     vec4 normal;
     vec4 position;
     vec4 color;
} vertex_in;

layout(location = 5000) uniform vec3 light;

out vec4 color;

#include "/happah/illumination.h.glsl"
#include "/happah/paint.h.glsl"

void main() {
     color = illuminate(light, vertex_in.normal.xyz, vertex_in.color);
}

