#version 400

layout(triangles, ccw) in;

in Vertex {
     vec4 position;
} vertex_in[];

uniform mat4x4 projectionMatrix;

out Vertex {
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

     float B10 = u4 + 2 * u3 * v;
     float B11 = u4 + 2 * u3 * w;
     float B07 = u4 + 2 * u3 * w + 6 * u3 * v + 6 * u2 * v * w + 12 * u2 * v2 + 6 * u * v2 * w + 6 * u * v3 + 2 * v3 * w + v4;
     float B08 = 6 * u4 + 24 * u3 * w + 24 * u2 * w2 + 8 * u * w3 + w4 + 24 * u3 * v + 60 * u2 * v * w + 36 * u * v * w2 + 6 * v * w3 + 24 * u2 * v2 + 36 * u * v2 * w + 12 * v2 * w2 + 8 * u * v3 + 6 * v3 * w + v4;
     float B09 = u4 + 6 * u3 * w + 12 * u2 * w2 + 6 * u * w3 + w4 + 2 * u3 * v + 6 * u2 * v * w + 6 * u * v * w2 + 2 * v * w3;
     float B03 = 2 * u * v3 + v4;
     float B04 = u4 + 6 * u3 * w + 12 * u2 * w2 + 6 * u * w3 + w4 + 8 * u3 * v + 36 * u2 * v * w + 36 * u * v * w2 + 8 * v * w3 + 24 * u2 * v2 + 60 * u * v2 * w + 24 * v2 * w2 + 24 * u * v3 + 24 * v3 * w + 6 * v4;
     float B05 = u4 + 8 * u3 * w + 24 * u2 * w2 + 24 * u * w3 + 6 * w4 + 6 * u3 * v + 36 * u2 * v * w + 60 * u * v * w2 + 24 * v * w3 + 12 * u2 * v2 + 36 * u * v2 * w + 24 * v2 * w2 + 6 * u * v3 + 8 * v3 * w + v4;
     float B06 = 2 * u * w3 + w4;
     float B00 = 2 * v3 * w + v4;
     float B01 = 2 * u * w3 + w4 + 6 * u * v * w2 + 6 * v * w3 + 6 * u * v2 * w + 12 * v2 * w2 + 2 * u * v3 + 6 * v3 * w + v4;
     float B02 = w4 + 2 * v * w3;

     vertex_out.position  = vertex_in[ 0].position * B00;
     vertex_out.position += vertex_in[ 1].position * B01;
     vertex_out.position += vertex_in[ 2].position * B02;
     vertex_out.position += vertex_in[ 3].position * B03;
     vertex_out.position += vertex_in[ 4].position * B04;
     vertex_out.position += vertex_in[ 5].position * B05;
     vertex_out.position += vertex_in[ 6].position * B06;
     vertex_out.position += vertex_in[ 7].position * B07;
     vertex_out.position += vertex_in[ 8].position * B08;
     vertex_out.position += vertex_in[ 9].position * B09;
     vertex_out.position += vertex_in[10].position * B10;
     vertex_out.position += vertex_in[11].position * B11;
     
     gl_Position = projectionMatrix * vertex_out.position;
}

