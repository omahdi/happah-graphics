// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Pawel Herman     - Added edge color.
// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.

//TODO: so far only general case

#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
     vec4 position;
     vec4 edgeColor;
     vec4 vertexColor;
} vertex_in[];

out Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} vertex_out;

out Triangle {
     flat vec4 edgeColor0;
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
     flat vec4 vertexColor0;
     flat vec4 vertexColor1;
     flat vec4 vertexColor2;
     flat vec3 maxheights;
} triangle_out;

void main() {
     vec4 v0 = vertex_in[0].position;
     vec4 v1 = vertex_in[1].position;
     vec4 v2 = vertex_in[2].position;
     
     float e0 = distance(v0.xyz, v1.xyz);
     float e1 = distance(v1.xyz, v2.xyz);
     float e2 = distance(v2.xyz, v0.xyz);
     float s = 0.5 * (e0 + e1 + e2);
     float t = sqrt(s * (s - e0) * (s - e1) * (s - e2));
     float h0 = (2.0 / e0) * t;
     float h1 = (2.0 / e1) * t;
     float h2 = (2.0 / e2) * t;
     
     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     vec4 normal = vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);
     
     vertex_out.dis = vec3(0, h1, 0);
     vertex_out.normal = normal;
     vertex_out.position = v0;
     gl_Position = gl_in[0].gl_Position;
     EmitVertex();

     vertex_out.dis = vec3(0, 0, h2);
     vertex_out.normal = normal;
     vertex_out.position = v1;
     gl_Position = gl_in[1].gl_Position;
     EmitVertex();

     triangle_out.edgeColor0 = vertex_in[0].edgeColor;
     triangle_out.edgeColor1 = vertex_in[1].edgeColor;
     triangle_out.edgeColor2 = vertex_in[2].edgeColor;
     triangle_out.vertexColor0 = vertex_in[0].vertexColor;
     triangle_out.vertexColor1 = vertex_in[1].vertexColor;
     triangle_out.vertexColor2 = vertex_in[2].vertexColor;
     triangle_out.maxheights = vec3(h0, h1, h2);
     vertex_out.dis = vec3(h0, 0, 0);
     vertex_out.normal = normal;
     vertex_out.position = v2;
     gl_Position = gl_in[2].gl_Position;
     EmitVertex();
     
     EndPrimitive();
}
