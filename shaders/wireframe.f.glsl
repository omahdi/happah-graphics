// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#version 430

in Vertex {
     noperspective vec3 dis;
     flat vec4 edgeColor0;
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
     vec4 normal;
     vec4 position;
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
     
     float range = 0.5 * w; //TODO: auf Pixel beziehen
     float alpha;
     
     if(d <= w - range) alpha = 1.0;
     else if(d <= w + range) {
          float x = (d - w + range) / range; 
          alpha = pow(2.0, -2.0 * x * x);
     } else alpha = 0.0;
     
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     color = alpha * color + (1.0 - alpha) * modelColor;
     color = (ambientCoefficient + diffuseCoefficient) * color;
}

