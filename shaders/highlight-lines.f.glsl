#version 430

in Vertex {
     vec4 normal;
     vec4 position;
};

layout(location = 5000) uniform vec4 bandColor0;
layout(location = 5001) uniform vec4 bandColor1;
layout(location = 5002) uniform float bandWidth;
layout(location = 5003) uniform vec3 beamDirection;
layout(location = 5004) uniform vec3 beamOrigin;
layout(location = 5005) uniform vec3 light;

out vec4 color;

void main() {
     vec3 v = normalize(cross(normalize(normal.xyz), beamDirection));
     uint k = uint(floor(abs(dot(v, beamOrigin - position.xyz / position.w)) / bandWidth));
     vec4 modelColor = ((k & 1) == 0) ? bandColor0 : bandColor1;
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     color = vec4((ambientCoefficient + diffuseCoefficient) * modelColor.rgb, modelColor.a);
}

