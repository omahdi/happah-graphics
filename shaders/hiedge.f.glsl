// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Pawel Herman     - Added edge color.
// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.
// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

#version 430
#extension GL_ARB_shading_language_include : require

in Vertex {
     noperspective vec3 dis;
     vec4 normal;
     vec4 position;
} vertex_in;

in Triangle {
     flat vec4 edgeColor0;
     flat vec4 edgeColor1;
     flat vec4 edgeColor2;
} triangle_in;

layout(location = 5000) uniform float edgeWidth;
layout(location = 5001) uniform vec3 light;
layout(location = 5002) uniform vec4 modelColor;
layout(location = 5003) uniform float squeezeScale;
layout(location = 5004) uniform float squeezeMin;

out vec4 color;

#include "/happah/illumination.h.glsl"

float aastep(float threshold, float d) {
     float w = 0.5 * fwidth(d);
     return smoothstep(threshold-w, threshold+w, d);
}

float fixstep(float strokeWidth, vec3 dis) {
     vec3 w = fwidth(dis);
     vec3 shade = smoothstep(w * ((strokeWidth * 0.5) - 0.5), w * ((strokeWidth * 0.5) + 0.5), dis);
     return 1.0 - min(min(shade.x, shade.y), shade.z);
}

vec3 fixstep_vec(float thickness, vec3 dis) {
     vec3 w = fwidth(dis);
     vec3 shade = smoothstep(w * ((thickness * 0.5) - 0.5), w * ((thickness * 0.5) + 0.5), dis);
     return 1.0 - shade;
}

#extension GL_OES_standard_derivatives : enable
void main() {
     const float PI = 3.14159265358;
     vec4 ec0 = triangle_in.edgeColor0;
     vec4 ec1 = triangle_in.edgeColor1;
     vec4 ec2 = triangle_in.edgeColor2;

     const vec3 dis = vertex_in.dis;
     vec3 hl = vec3(ec0.a, ec1.a, ec2.a);

     float d = min(min(dis.x, dis.y), dis.z);
     float t = max(dis.x, dis.y);
     if (dis.y < dis.x && dis.y < dis.z)
          t = 1.0 - t;

     float s = sin(t*PI);
     float strokeWidth = edgeWidth * mix(squeezeMin, squeezeScale, (1.0 - s));
     //float edgeAlpha = 1.0 - aastep(0.01*strokeWidth, d);
     //float edgeAlpha = fixstep(strokeWidth, dis);
     vec3 edgeShade = fixstep_vec(strokeWidth, dis);
     float alpha = 1.0 - max(max(edgeShade.x, edgeShade.y), edgeShade.z);
     vec3 filt = 1.0 - step(edgeShade, vec3(alpha));
     float beta = (filt.x + filt.y + filt.z);
     vec4 stroke = (filt.x*ec0 + filt.y*ec1 + filt.z*ec2) / beta;
     stroke.a = 1.0;
     vec4 xcolor = illuminate(vertex_in.normal.xyz, light, mix(stroke, modelColor, alpha));
     //vec4 xcolor = vec4(0.0, 0.2, 0.2, 1.0);
     xcolor = mix(stroke, xcolor, alpha);

     if (false) {
          vec3 strokedef = vec3(0.5, 0.5, 0.5);
          vec3 filldef = vec3(1.0, 1.0, 1.0);
          vec4 xcolor = vec4(0.0);
          if (false) {
               xcolor = vec4(strokedef, edgeShade);
               if (!gl_FrontFacing)
                    xcolor.rgb = vec3(1.0, 0.0, 0.0);
          } else {
               vec3 mainStroke = mix(filldef, strokedef, edgeShade);
               xcolor.a = 1.0;
               if (false) {
                    float inner = 1.0 - aastep(2*edgeWidth, d);
                    vec3 wireColor = mix(filldef, strokedef, abs(inner - edgeShade));
                    xcolor.rgb = wireColor;
               } else {
                    xcolor.rgb = mainStroke;
               }
          }
     }
     color = xcolor;

     if (false) {
          vec3 thickness = vec3(max(dis.y, dis.z), max(dis.x, dis.z), max(dis.x, dis.y));
          //thickness = step(fract(8.0*thickness), vec3(0.5));
          vec3 w = fwidth(dis);    // gl_FragCoord.w*fwidth(dis);
          vec3 range = edgeWidth*max(max(vec3(squeezeMin), squeezeScale*thickness), hl);
          vec3 shade = smoothstep(range-w, range+w, dis);
          float alpha = min(min(shade.x, shade.y), shade.z);
          //float gamma = min(min(max(shade.y, shade.z), max(shade.x, shade.z)), max(shade.x, shade.y));
          //float alpha = min(gamma, min(min(shade.x, shade.y), shade.z));
          vec3 filt = 1.0 - sign(shade-vec3(alpha));
          //vec3 filt = sign(1.0-shade);
          float beta = (filt.x + filt.y + filt.z);
          vec4 ec = (filt.x*ec0 + filt.y*ec1 + filt.z*ec2) / beta;
          ec.a = 1.0;
          vec4 lmc = illuminate(vertex_in.normal.xyz, light, mix(ec, modelColor, alpha));
          color = mix(ec, lmc, alpha);
     }
     //color = mix(mix(lmc, modelColor, 0.7), ec, 1.0-alpha);
     //color = mix(mix(lmc, modelColor, 0.7), ec, 1.0 - alpha);
     //color = vec4(alpha, alpha, alpha, 1.0);
     //color = vec4(mix(vec3(0.2), vec3(1.0), alpha), 1.0);
}
