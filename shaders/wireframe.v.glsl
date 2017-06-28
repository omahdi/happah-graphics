#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 edgeColor;

layout(location = 1000) uniform mat4x4 modelViewMatrix;
layout(location = 1001) uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 edgeColor;
     vec4 position;
} phm_out;

void main() {
     phm_out.edgeColor = edgeColor;
     phm_out.position = modelViewMatrix * position;
     gl_Position = projectionMatrix * phm_out.position;
}

