#version 430
//Hedwig Amberg
//Implementation of "Solid Wireframe" white paper
//TODO: no anti-aliasing 

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
};

layout(location = 5000) uniform vec4 edgeColor;
layout(location = 5001) uniform float edgeWidth;
layout(location = 5002) uniform vec3 light;

out vec4 color;

void main() {
     float d = min(dis.x, min(dis.y, dis.z));
     float w = 0.5 * bandWidth;
     
     if(d <= w){
          float ambientCoefficient = 0.4;
          float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
          color = vec4((ambientCoefficient + diffuseCoefficient) * edgeColor.rgb, edgeColor.a);
     }else{ 
          discard;
     }
}
