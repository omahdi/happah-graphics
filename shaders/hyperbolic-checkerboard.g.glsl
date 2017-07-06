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
     vec2 hyp_uv;
} vertex_in[];

out Vertex {
     vec4 position;
     vec3 barycentric;
     noperspective vec2 hyp_uv;
} vertex_out;

out Triangle {
     flat vec3 abc2;
     flat vec4 normal;
} triangle_out;

void main() {
     vec4 v0 = vertex_in[0].position;
     vec4 v1 = vertex_in[1].position;
     vec4 v2 = vertex_in[2].position;

     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     vec4 normal = vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);

     vertex_out.position = v0;
     vertex_out.barycentric = vec3(1.0, 0.0, 0.0);
     vertex_out.hyp_uv = vertex_in[0].hyp_uv;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();
     vertex_out.position = v1;
     vertex_out.barycentric = vec3(0.0, 1.0, 0.0);
     vertex_out.hyp_uv = vertex_in[1].hyp_uv;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();
     vertex_out.position = v2;
     vertex_out.barycentric = vec3(0.0, 0.0, 1.0);
     vertex_out.hyp_uv = vertex_in[2].hyp_uv;
     triangle_out.abc2 = vec3(length2(w2-w1), length2(w2-w0), length2(w1-w0));
     triangle_out.normal = normal;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();
     EndPrimitive();
}
