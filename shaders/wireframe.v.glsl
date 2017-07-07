// Copyright 2017
//   Pawel Herman  - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Hedwig Amberg    - added colored vertices for better path appearance.

#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 edgeFlag;

layout(location = 1000) uniform mat4x4 modelViewMatrix;
layout(location = 1001) uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 position;
     int edgeFlag;
} phm_out;

void main() {
     phm_out.position = modelViewMatrix * position;
     phm_out.edgeFlag = (edgeFlag.x > 0.9) ? 1 : 0;
     gl_Position = projectionMatrix * phm_out.position;
}

