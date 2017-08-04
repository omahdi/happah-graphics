// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.07 - Hedwig Amberg    - add new shader for coloring triangles individualy.
// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

#version 400
#extension GL_ARB_shading_language_include : require

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
     vec4 color;
} vertex_in[];

out Vertex {
     vec4 normal;
     vec4 position;
     vec4 color;
} vertex_out;

#include "/happah/geometry.h.glsl"

void main() {
     vec4 v0 = vertex_in[0].position;
     vec4 v1 = vertex_in[1].position;
     vec4 v2 = vertex_in[2].position;
     
     vec4 normal = calc_normal(v0, v1, v2);

     vertex_out.normal = normal;
     vertex_out.position = v0;
     vertex_out.color = vertex_in[0].color;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();

     vertex_out.normal = normal;
     vertex_out.position = v1;
     vertex_out.color = vertex_in[1].color;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();

     vertex_out.normal = normal;
     vertex_out.position = v2;
     vertex_out.color = vertex_in[2].color;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();

     EndPrimitive();
}

