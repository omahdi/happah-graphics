// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Pawel Herman     - Added edge color.
// 2017.06 - Hedwig Amberg    - added colored vertices for better path appearance.

//TODO: range auf Pixel beziehen ~2 Pixel antialiasing

#version 430

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
};

in Triangle {
     flat vec4 edgeColor0;
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
     flat vec4 vertexColor0;
     flat vec4 vertexColor1;
     flat vec4 vertexColor2;
     flat vec3 maxheights;
};

layout(location = 5000) uniform vec4 edgeColor;
layout(location = 5001) uniform float edgeWidth;
layout(location = 5002) uniform vec3 light;
layout(location = 5003) uniform vec4 modelColor;

out vec4 color;

void main() {
     float d = min(dis.x, min(dis.y, dis.z));
     color = (dis.y < dis.z) ? ((dis.x < dis.y) ? edgeColor0 : edgeColor1) : ((dis.x < dis.z) ? edgeColor0 : edgeColor2);
     float w = 0.5 * edgeWidth;
     float range = 0.1 * w;
     float alpha = 1.0;
     
     if(d <= w - range) alpha = 1.0;
     else if(d <= w + range) {
          float x = (d - w + range) / range; 
          alpha = pow(2.0, -2.0 * x * x);
     } else alpha = 0.0;
     
     float vertexRange0 = maxheights.y - dis.y;
     float vertexRange1 = maxheights.z - dis.z;
     float vertexRange2 = maxheights.x - dis.x;
     float vertd = min(vertexRange0, min(vertexRange1, vertexRange2));
     vec4 vertexColor = vec4(0,0,0,0);
     
     if(vertexRange0 <= w + range){
          vertexColor = vertexColor0;
     }else if(vertexRange1 <= w + range){
          vertexColor = vertexColor1;
     }else if(vertexRange2 <= w + range){
          vertexColor = vertexColor2;
     }
     
     float beta = 1.0;
     
     if(vertd <= w - range){
          beta = 1.0;
     } else if(vertd <= w + range) {
          float x = (vertd - w + range) / range; 
          beta = pow(2.0, -2.0 * x * x);
     } else beta = 0.0;
     
     
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     color = alpha * color + (1.0 - alpha) * modelColor;
     color = beta * vertexColor + (1.0 - beta) * color;
     color = (ambientCoefficient + diffuseCoefficient) * color;
}

