// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

#version 400
#extension GL_ARB_shading_language_include : require

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
     vec4 color;              //color of the triangle at this vertex
     vec4 edgeColor;          //color of the edge associated with this vertex
     vec4 edgeVertexColor;    //color of the vertex, so paths are connected
} vertex_in[];

out Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
     vec4 color;              //color of the traingle at this vertex, to be interpolated
} vertex_out;

out Triangle {
     flat vec4 edgeColor0;    //fixed edge colors and vertex colors
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
     flat vec4 vertexColor0;
     flat vec4 vertexColor1;
     flat vec4 vertexColor2;
     flat vec3 maxheights;
} triangle_out;

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
     vertex_out.color = vertex_in[0].color;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();

     vertex_out.dis = vec3(0, 0, heights.z);
     vertex_out.normal = normal;
     vertex_out.position = v1;
     vertex_out.color = vertex_in[1].color;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();

     triangle_out.edgeColor0 = vertex_in[0].edgeColor;
     triangle_out.edgeColor1 = vertex_in[1].edgeColor;
     triangle_out.edgeColor2 = vertex_in[2].edgeColor;
     triangle_out.vertexColor0 = vertex_in[0].edgeVertexColor;
     triangle_out.vertexColor1 = vertex_in[1].edgeVertexColor;
     triangle_out.vertexColor2 = vertex_in[2].edgeVertexColor;
     triangle_out.maxheights = vec3(heights.x, heights.y, heights.z);

     vertex_out.dis = vec3(heights.x, 0, 0);
     vertex_out.normal = normal;
     vertex_out.position = v2;
     vertex_out.color = vertex_in[2].color;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();

     EndPrimitive();
}
