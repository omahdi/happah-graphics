// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.07 - Hedwig Amberg    - add new shader for coloring triangles individualy.

#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

layout(location = 1000) uniform mat4x4 modelViewMatrix;
layout(location = 1001) uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 position;
     vec4 color;
} vertex_out;

void main() {
     vertex_out.position = modelViewMatrix * position;
     vertex_out.color = color;
     gl_Position = projectionMatrix * vertex_out.position;
}

