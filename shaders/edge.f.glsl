// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Pawel Herman     - Added edge color.
// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.

//TODO: range auf Pixel beziehen ~2 Pixel antialiasing

#version 430
#extension GL_ARB_shading_language_include : require

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} vertex_in;

in Triangle {
     flat vec4 edgeColor0;
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
     flat vec4 vertexColor0;
     flat vec4 vertexColor1;
     flat vec4 vertexColor2;
     flat vec3 maxheights;
} triangle_in;

layout(location = 5000) uniform float edgeWidth;
layout(location = 5001) uniform vec3 light;
layout(location = 5002) uniform vec4 modelColor;

out vec4 color;

#include "/happah/illumination.h.glsl"

void main() {
     float d = min(vertex_in.dis.x, min(vertex_in.dis.y, vertex_in.dis.z));
     color = (vertex_in.dis.y < vertex_in.dis.z) ? ((vertex_in.dis.x < vertex_in.dis.y) ? triangle_in.edgeColor0 : triangle_in.edgeColor1) : ((vertex_in.dis.x < vertex_in.dis.z) ? triangle_in.edgeColor0 : triangle_in.edgeColor2);
     float w = 0.5 * edgeWidth;
     float range = 0.1 * w;
     float alpha = 1.0;
     
     if(d <= w - range) alpha = 1.0;
     else if(d <= w + range) {
          float x = (d - w + range) / range; 
          alpha = pow(2.0, -2.0 * x * x);
     } else alpha = 0.0;
     
     float vertexRange0 = triangle_in.maxheights.y - vertex_in.dis.y;
     float vertexRange1 = triangle_in.maxheights.z - vertex_in.dis.z;
     float vertexRange2 = triangle_in.maxheights.x - vertex_in.dis.x;
     float vertd = min(vertexRange0, min(vertexRange1, vertexRange2));
     vec4 vertexColor = vec4(0,0,0,0);
     
     if(vertexRange0 <= w + range){
          vertexColor = triangle_in.vertexColor0;
     }else if(vertexRange1 <= w + range){
          vertexColor = triangle_in.vertexColor1;
     }else if(vertexRange2 <= w + range){
          vertexColor = triangle_in.vertexColor2;
     }
     
     float beta = 1.0;
     
     if(vertd <= w - range){
          beta = 1.0;
     } else if(vertd <= w + range) {
          float x = (vertd - w + range) / range; 
          beta = pow(2.0, -2.0 * x * x);
     } else beta = 0.0;
     
     color = alpha * color + (1.0 - alpha) * modelColor;
     color = beta * vertexColor + (1.0 - beta) * color;
     color = illuminate(light, vertex_in.normal.xyz, color);
}

