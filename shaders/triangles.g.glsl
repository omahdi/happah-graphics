// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.07 - Hedwig Amberg    - add new shader for coloring triangles individualy.

#version 400

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

void main() {
     vec4 v0 = vertex_in[0].position;
     vec4 v1 = vertex_in[1].position;
     vec4 v2 = vertex_in[2].position;
     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     vec4 normal = vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);

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

