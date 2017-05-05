#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
} phm_in[];

out Vertex {
     vec4 normal;
     vec4 position;
} phm_out;

void main() {
     vec4 v0 = phm_in[0].position;
     vec4 v1 = phm_in[1].position;
     vec4 v2 = phm_in[2].position;
     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     vec4 normal = vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);
     phm_out.normal = normal;
     phm_out.position = v0;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();
     phm_out.normal = normal;
     phm_out.position = v1;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();
     phm_out.normal = normal;
     phm_out.position = v2;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();
     EndPrimitive();
}

