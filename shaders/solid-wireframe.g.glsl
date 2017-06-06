#Hedwig Amberg
#Implementation of "Solid Wireframe" white paper
#TODO: so far only general case

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
} phm_in[];

out Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} phm_out;

void main() {
     vec4 v0 = phm_in[0].position;
     vec4 v1 = phm_in[1].position;
     vec4 v2 = phm_in[2].position;
     
     float e0 = distance((vec3) v0, (vec3) v1);
     float e1 = distance((vec3) v1, (vec3) v2);
     float e2 = distance((vec3) v2, (vec3) v0);
     float s = 0.5 * (e0 + e1 + e2);
     folat t = sqrt(s * (s - e0) * (s - e1) * (s - e2));
     float h0 = (2.0 / e0) * t;
     float h1 = (2.0 / e1) * t;
     float h2 = (2.0 / e2) * t;
     
     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     vec4 normal = vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);
     
     phm_out.dis = vec3(0, h1, 0);
     phm_out.normal = normal;
     phm_out.position = v0;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();

     phm_out.dis = vec3(0, 0, h2);
     phm_out.normal = normal;
     phm_out.position = v1;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();

     phm_out.dis = vec3(h0, 0, 0);
     phm_out.normal = normal;
     phm_out.position = v2;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();
     
     EndPrimitive();
}
