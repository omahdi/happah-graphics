#version 430

layout(location = 0) in vec4 position;

layout(location = 1000) uniform mat4x4 modelViewMatrix;
layout(location = 1001) uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 position;
} vertex_out;

void main() {
     vertex_out.position = modelViewMatrix * position;
     gl_Position = projectionMatrix * vertex_out.position;
}

