// Copyright 2017
//   Pawel Herman   - Karlsruhe Institute of Technology - pherman@ira.uka.de
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#version 400

layout(triangles, ccw) in;

in Vertex {
     vec4 position;
} vertex_in[];

uniform mat4x4 projectionMatrix;

out Vertex {
     vec4 normal;
     vec4 position;
} vertex_out;

void main() {
     float u = gl_TessCoord.x;
     float v = gl_TessCoord.y;
     float w = gl_TessCoord.z;

     float u2 = u  * u ;
     float u3 = u2 * u ;
     float u4 = u2 * u2;
     float v2 = v  * v ;
     float v3 = v2 * v ;
     float v4 = v2 * v2;
     float w2 = w  * w ;
     float w3 = w2 * w ;
     float w4 = w2 * w2;

     float B30 =     u3          ;
     float B31 = 3 * u2 * v      ;
     float B32 = 3 * u  * v2     ;
     float B33 =          v3     ;
     float B34 = 3 * u2 *      w ;
     float B35 = 6 * u  * v  * w ;
     float B36 = 3 *      v2 * w ;
     float B37 = 3 * u *       w2;
     float B38 = 3 *      v  * w2;
     float B39 =               w3;

     float B400 =      u4          ;
     float B401 =  4 * u3 * v      ;
     float B402 =  6 * u2 * v2     ;
     float B403 =  4 * u  * v3     ;
     float B404 =           v4     ;
     float B405 =  4 * u3 *      w ;
     float B406 = 12 * u2 * v  * w ;
     float B407 = 12 * u  * v2 * w ;
     float B408 =  4 *      v3 * w ;
     float B409 =  6 * u2 *      w2;
     float B410 = 12 * u  * v  * w2;
     float B411 =  6 *      v2 * w2;
     float B412 =  4 * u  *      w3;
     float B413 =  4 *      v  * w3;
     float B414 =                w4;

     vertex_out.position  = vertex_in[ 0].position * B400;
     vertex_out.position += vertex_in[ 1].position * B401;
     vertex_out.position += vertex_in[ 2].position * B402;
     vertex_out.position += vertex_in[ 3].position * B403;
     vertex_out.position += vertex_in[ 4].position * B404;
     vertex_out.position += vertex_in[ 5].position * B405;
     vertex_out.position += vertex_in[ 6].position * B406;
     vertex_out.position += vertex_in[ 7].position * B407;
     vertex_out.position += vertex_in[ 8].position * B408;
     vertex_out.position += vertex_in[ 9].position * B409;
     vertex_out.position += vertex_in[10].position * B410;
     vertex_out.position += vertex_in[11].position * B411;
     vertex_out.position += vertex_in[12].position * B412;
     vertex_out.position += vertex_in[13].position * B413;
     vertex_out.position += vertex_in[14].position * B414;

     vec4 t0 = vec4(0.0);
     t0 += (vertex_in[ 1].position - vertex_in[ 0].position) * B30;
     t0 += (vertex_in[ 2].position - vertex_in[ 1].position) * B31;
     t0 += (vertex_in[ 3].position - vertex_in[ 2].position) * B32;
     t0 += (vertex_in[ 4].position - vertex_in[ 3].position) * B33;
     t0 += (vertex_in[ 6].position - vertex_in[ 5].position) * B34;
     t0 += (vertex_in[ 7].position - vertex_in[ 6].position) * B35;
     t0 += (vertex_in[ 8].position - vertex_in[ 7].position) * B36;
     t0 += (vertex_in[10].position - vertex_in[ 9].position) * B37;
     t0 += (vertex_in[11].position - vertex_in[10].position) * B38;
     t0 += (vertex_in[13].position - vertex_in[12].position) * B39;

     vec4 t1 = vec4(0.0);
     t1 += (vertex_in[ 5].position - vertex_in[ 0].position) * B30;
     t1 += (vertex_in[ 6].position - vertex_in[ 1].position) * B31;
     t1 += (vertex_in[ 7].position - vertex_in[ 2].position) * B32;
     t1 += (vertex_in[ 8].position - vertex_in[ 3].position) * B33;
     t1 += (vertex_in[ 9].position - vertex_in[ 5].position) * B34;
     t1 += (vertex_in[10].position - vertex_in[ 6].position) * B35;
     t1 += (vertex_in[11].position - vertex_in[ 7].position) * B36;
     t1 += (vertex_in[12].position - vertex_in[ 9].position) * B37;
     t1 += (vertex_in[13].position - vertex_in[10].position) * B38;
     t1 += (vertex_in[14].position - vertex_in[12].position) * B39;

     vertex_out.normal = vec4(normalize(cross(t0.xyz, t1.xyz)), 0.0);
     gl_Position = projectionMatrix * vertex_out.position;
}

