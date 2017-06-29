// Copyright 2017
//   Obada Mahdi - Karlsruhe Institute of Technology - omahdi@gmail.com
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based off wireframe shader

#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
     vec3 hyp_uv;
} vertex_in[];

out Vertex {
     vec4 position;
     noperspective vec2 hyp_uv;
} vertex_out;

out Triangle {
     flat vec4 normal;
} triangle_out;

void main() {
     vec4 v0 = vertex_in[0].position;
     vec3 h0 = vertex_in[0].hyp_uv;
     vec4 v1 = vertex_in[1].position;
     vec3 h1 = vertex_in[1].hyp_uv;
     vec4 v2 = vertex_in[2].position;
     vec3 h2 = vertex_in[2].hyp_uv;

     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     vec4 normal = vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);

     vertex_out.position = v0;
     vertex_out.hyp_uv = h0.xy;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();
     vertex_out.position = v1;
     vertex_out.hyp_uv = h1.xy;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();
     vertex_out.position = v2;
     vertex_out.hyp_uv = h2.xy;
     triangle_out.normal = normal;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();
     EndPrimitive();
}
