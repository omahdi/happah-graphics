// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.
// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

//TODO: so far only general case

#version 400
#extension GL_ARB_shading_language_include : require

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
} vertex_in[];

out Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} vertex_out;

#include "/happah/geometry.h.glsl"

void main() {
     vec4 v0 = vertex_in[0].position;
     vec4 v1 = vertex_in[1].position;
     vec4 v2 = vertex_in[2].position;
     
     vec3 heights = calc_heights(v0, v1, v2);
     vec4 normal = calc_normal(v0, v1, v2);
     
     vertex_out.dis = vec3(0, heights.y, 0);
     vertex_out.normal = normal;
     vertex_out.position = v0;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();

     vertex_out.dis = vec3(0, 0, heights.z);
     vertex_out.normal = normal;
     vertex_out.position = v1;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();

     vertex_out.dis = vec3(heights.x, 0, 0);
     vertex_out.normal = normal;
     vertex_out.position = v2;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();
     
     EndPrimitive();
}
