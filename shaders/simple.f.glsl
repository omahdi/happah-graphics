#version 430

in Vertex {
     vec4 normal;
     vec4 position;
};

layout(location = 5000) uniform vec3 light;
layout(location = 5001) uniform vec4 modelColor;

out vec4 color;

void main() {
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz / normal.w), light));
     color = vec4((ambientCoefficient + diffuseCoefficient) * modelColor.rgb, modelColor.a);
}

