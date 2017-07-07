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
     //flat vec4 vertexColor0;
     //flat vec4 vertexColor1;
     //flat vec4 vertexColor2;
     flat ivec3 edgeFlag;
};

layout(location = 5000) uniform vec4 edgeColor;
layout(location = 5001) uniform float edgeWidth;
layout(location = 5002) uniform vec3 light;
layout(location = 5003) uniform vec4 modelColor;

out vec4 color;

void main() {
     float d = min(dis.x, min(dis.y, dis.z));
     //color = (dis.y < dis.z) ? ((dis.x < dis.y) ? edgeColor0 : edgeColor1) : ((dis.x < dis.z) ? edgeColor0 : edgeColor2);
     float w = 0.5 * edgeWidth;
     float range = 0.2 * w;
     float alpha = 1.0;
     vec4 xcol = edgeColor0;
     //if (edgeFlag.x != 0 && dis.x <= w-range || edgeFlag.y != 0 && dis.y <= w-range || edgeFlag.z != 0 && dis.z < w-range)
     if (edgeFlag.x != 0 && dis.x <= w+range && dis.x < dis.y && dis.x < dis.z) {
          xcol = edgeColor1;
     } else if (edgeFlag.y != 0 && dis.y <= w+range && dis.y < dis.x && dis.y < dis.z) {
          xcol = edgeColor1;
     } else if (edgeFlag.z != 0 && dis.z < w+range && dis.z < dis.x && dis.z < dis.y) {
          xcol = edgeColor1;
     } else {
          w = 0.5*w;
     }

     if(d <= w - range) alpha = 1.0;
     else if(d <= w + range) {
          float x = (d - w + range) / range; 
          alpha = pow(2.0, -2.0 * x * x);
     } else alpha = 0.0;
     
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     //color = mix(modelColor*(ambientCoefficient + diffuseCoefficient), xcol, alpha);
     color = alpha*xcol + (1-alpha)*(ambientCoefficient + diffuseCoefficient)*modelColor;
     //color = (ambientCoefficient + diffuseCoefficient)*(alpha*xcol + (1-alpha)*modelColor);
}

