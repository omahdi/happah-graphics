// Copyright 2017
//   Pawel Herman  - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in Vertex {
     vec4 position;
} vertex_in[];

layout(location = 1001) uniform mat4 projectionMatrix;
layout(location = 4001) uniform float radius;

out Vertex {
     vec2 billboard;
     flat vec4 center;
} vertex_out;

void main() {
     vec4 center = vertex_in[0].position;

     vertex_out.center = center;
     vertex_out.billboard = vec2(-1.0f, -1.0f);
     gl_Position = projectionMatrix * vec4(center.x - radius, center.y - radius, center.z, center.w);
     EmitVertex();

     vertex_out.center = center;
     vertex_out.billboard = vec2(-1.0f, 1.0f);
     gl_Position = projectionMatrix * vec4(center.x - radius, center.y + radius, center.z, center.w);
     EmitVertex();

     vertex_out.center = center;
     vertex_out.billboard = vec2(1.0f, -1.0f);
     gl_Position = projectionMatrix * vec4(center.x + radius, center.y - radius, center.z, center.w);
     EmitVertex();
     
     vertex_out.center = center;
     vertex_out.billboard = vec2(1.0f, 1.0f);
     gl_Position = projectionMatrix * vec4(center.x + radius, center.y + radius, center.z, center.w);
     EmitVertex();

     EndPrimitive();
}

