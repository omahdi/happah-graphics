//Hedwig Amberg - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//Implementation of "Solid Wireframe" white paper
#version 430

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
};

layout(location = 5000) uniform vec4 modelColor;
layout(location = 5001) uniform vec4 edgeColor;
layout(location = 5002) uniform float edgeWidth;
layout(location = 5003) uniform vec3 light;

out vec4 color;

void main() {
     float d = min(dis.x, min(dis.y, dis.z));
     float w = 0.5 * edgeWidth;
     
     float range = 0.5 * w; //TODO: auf Pixel beziehen
     float opacity;
     
     if(d <= w - range){
          opacity= 1.0;
     }else if(d <= w + range){
          float x = (d - w + range) / range; 
          opacity = pow(2.0, -2.0 * x * x);
     }else{ 
          //discard;
          opacity = 0.0;
     }
     
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     color = vec4((ambientCoefficient + diffuseCoefficient) * edgeColor.rgb, opacity);
}
