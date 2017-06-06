#Hedwig Amberg
#Implementation of "Solid Wireframe" white paper
#TODO: no anti-aliasing 

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
};

layout(location = 5000) uniform vec4 bandColor;
layout(location = 5001) uniform float bandWidth;
layout(location = 5002) uniform vec3 beamDirection;
layout(location = 5003) uniform vec3 beamOrigin;
layout(location = 5004) uniform vec3 light;

out vec4 color;

void main() {
     float d = min(dis.x, min(dis.y, dis.z));
     float w = 0.5 * bandWidth;
     
     if(d <= w){
          float ambientCoefficient = 0.4;
          float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
          color = vec4((ambientCoefficient + diffuseCoefficient) * bandColor0.rgb, bandColor0.a);
     }else{ 
          discard;
     }
}
