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
     float u5 = u4 * u ;
     float v2 = v  * v ;
     float v3 = v2 * v ;
     float v4 = v2 * v2;
     float v5 = v4 * v ;
     float w2 = w  * w ;
     float w3 = w2 * w ;
     float w4 = w2 * w2;
     float w5 = w4 * w ;

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

     float B500 =      u5          ;
     float B501 =  5 * u4 * v      ;
     float B502 = 10 * u3 * v2     ;
     float B503 = 10 * u2 * v3     ;
     float B504 =  5 * u  * v4     ;
     float B505 =           v5     ;
     float B506 =  5 * u4 *      w ;
     float B507 = 20 * u3 * v  * w ;
     float B508 = 30 * u2 * v2 * w ;
     float B509 = 20 * u  * v3 * w ;
     float B510 =  5 *      v4 * w ;
     float B511 = 10 * u3 *      w2;
     float B512 = 30 * u2 * v  * w2;
     float B513 = 30 * u  * v2 * w2;
     float B514 = 10 *      v3 * w2;
     float B515 = 10 * u2 *      w3;
     float B516 = 20 * u  * v  * w3;
     float B517 = 10 *      v2 * w3;
     float B518 =  5 * u  *      w4;
     float B519 =  5 *      v  * w4;
     float B520 =                w5;

     vertex_out.position  = vertex_in[ 0].position * B500;
     vertex_out.position += vertex_in[ 1].position * B501;
     vertex_out.position += vertex_in[ 2].position * B502;
     vertex_out.position += vertex_in[ 3].position * B503;
     vertex_out.position += vertex_in[ 4].position * B504;
     vertex_out.position += vertex_in[ 5].position * B505;
     vertex_out.position += vertex_in[ 6].position * B506;
     vertex_out.position += vertex_in[ 7].position * B507;
     vertex_out.position += vertex_in[ 8].position * B508;
     vertex_out.position += vertex_in[ 9].position * B509;
     vertex_out.position += vertex_in[10].position * B510;
     vertex_out.position += vertex_in[11].position * B511;
     vertex_out.position += vertex_in[12].position * B512;
     vertex_out.position += vertex_in[13].position * B513;
     vertex_out.position += vertex_in[14].position * B514;
     vertex_out.position += vertex_in[15].position * B515;
     vertex_out.position += vertex_in[16].position * B516;
     vertex_out.position += vertex_in[17].position * B517;
     vertex_out.position += vertex_in[18].position * B518;
     vertex_out.position += vertex_in[19].position * B519;
     vertex_out.position += vertex_in[20].position * B520;

     vec4 t0 = vec4(0.0);
     t0 += (vertex_in[ 1].position - vertex_in[ 0].position) * B400;
     t0 += (vertex_in[ 2].position - vertex_in[ 1].position) * B401;
     t0 += (vertex_in[ 3].position - vertex_in[ 2].position) * B402;
     t0 += (vertex_in[ 4].position - vertex_in[ 3].position) * B403;
     t0 += (vertex_in[ 5].position - vertex_in[ 4].position) * B404;
     t0 += (vertex_in[ 7].position - vertex_in[ 6].position) * B405;
     t0 += (vertex_in[ 8].position - vertex_in[ 7].position) * B406;
     t0 += (vertex_in[ 9].position - vertex_in[ 8].position) * B407;
     t0 += (vertex_in[10].position - vertex_in[ 9].position) * B408;
     t0 += (vertex_in[12].position - vertex_in[11].position) * B409;
     t0 += (vertex_in[13].position - vertex_in[12].position) * B410;
     t0 += (vertex_in[14].position - vertex_in[13].position) * B411;
     t0 += (vertex_in[16].position - vertex_in[15].position) * B412;
     t0 += (vertex_in[17].position - vertex_in[16].position) * B413;
     t0 += (vertex_in[19].position - vertex_in[18].position) * B414;

     vec4 t1 = vec4(0.0);
     t1 += (vertex_in[ 6].position - vertex_in[ 0].position) * B400;
     t1 += (vertex_in[ 7].position - vertex_in[ 1].position) * B401;
     t1 += (vertex_in[ 8].position - vertex_in[ 2].position) * B402;
     t1 += (vertex_in[ 9].position - vertex_in[ 3].position) * B403;
     t1 += (vertex_in[10].position - vertex_in[ 4].position) * B404;
     t1 += (vertex_in[11].position - vertex_in[ 6].position) * B405;
     t1 += (vertex_in[12].position - vertex_in[ 7].position) * B406;
     t1 += (vertex_in[13].position - vertex_in[ 8].position) * B407;
     t1 += (vertex_in[14].position - vertex_in[ 9].position) * B408;
     t1 += (vertex_in[15].position - vertex_in[11].position) * B409;
     t1 += (vertex_in[16].position - vertex_in[12].position) * B410;
     t1 += (vertex_in[17].position - vertex_in[13].position) * B411;
     t1 += (vertex_in[18].position - vertex_in[15].position) * B412;
     t1 += (vertex_in[19].position - vertex_in[16].position) * B413;
     t1 += (vertex_in[20].position - vertex_in[18].position) * B414;

     vertex_out.normal = vec4(normalize(cross(t0.xyz, t1.xyz)), 0.0);
     gl_Position = projectionMatrix * vertex_out.position;
}

