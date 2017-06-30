// Copyright 2017
//   Pawel Herman  - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 edgeColor;
layout(location = 2) in vec4 vertexColor;

layout(location = 1000) uniform mat4x4 modelViewMatrix;
layout(location = 1001) uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 position;
     vec4 edgeColor;
     vec4 vertexColor;
} phm_out;

void main() {
     phm_out.edgeColor = edgeColor;
     phm_out.vertexColor = vertexColor;
     phm_out.position = modelViewMatrix * position;
     gl_Position = projectionMatrix * phm_out.position;
}

