#version 430
#extension GL_ARB_shading_language_include : require

in Vertex {
     vec4 normal;
     vec4 position;
} vertex_in;

layout(location = 5000) uniform vec3 light;
layout(location = 5001) uniform vec4 modelColor;

out vec4 color;

#include "/happah/illumination.h.glsl"

void main() { color = illuminate(light, vertex_in.normal.xyz, modelColor); }

