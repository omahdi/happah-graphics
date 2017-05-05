#version 430

in Vertex {
     vec4 normal;
     vec4 position;
};

layout(location = 5000) uniform vec4 modelColor;
layout(location = 5001) uniform vec3 light;

out vec4 color;

void main() {
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz / normal.w), light));
     color = vec4((ambientCoefficient + diffuseCoefficient) * modelColor.rgb, modelColor.a);
}

