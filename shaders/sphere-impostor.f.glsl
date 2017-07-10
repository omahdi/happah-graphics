// Copyright 2017
//   Pawel Herman  - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#version 430

in Vertex {
     vec2 billboard;
     flat vec4 center;
} vertex_in;

layout(location = 5000) uniform vec3 light;
layout(location = 5001) uniform vec4 modelColor;
layout(location = 1001) uniform mat4 projectionMatrix;
layout(location = 4001) uniform float radius;

out vec4 color;

void main() {
     float x = vertex_in.billboard.x;
     float y = vertex_in.billboard.y;
     float z2 = 1.0f - x * x - y * y;
    
     if(z2 <= 0.0f) discard;
     float z = sqrt(z2);
     
     vec3 normal = vec3(x, y, z);

     vec4 position = projectionMatrix * vec4(vertex_in.center.xyz + radius * normal, 1.0);
     float ndcDepth = position.z / position.w;

     gl_FragDepth = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;

     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     color = vec4((ambientCoefficient + diffuseCoefficient) * modelColor.rgb, modelColor.a);
}

