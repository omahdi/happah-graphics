// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 edgeColor;
layout(location = 3) in vec4 edgeVertexColor;

layout(location = 1000) uniform mat4x4 modelViewMatrix;
layout(location = 1001) uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 position;
     vec4 color;              //color of the triangle at this vertex
     vec4 edgeColor;          //color of the edge associated with this vertex
     vec4 edgeVertexColor;    //color of the vertex, so paths are connected
} vertex_out;

void main() {
     vertex_out.position = modelViewMatrix * position;
     vertex_out.color = color;
     vertex_out.edgeColor = edgeColor;
     vertex_out.edgeVertexColor = edgeVertexColor;
     gl_Position = projectionMatrix * vertex_out.position;
}