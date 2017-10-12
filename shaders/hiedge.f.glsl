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

#extension GL_OES_standard_derivatives : enable
void main() {
     vec4 ec0 = triangle_in.edgeColor0;
     vec4 ec1 = triangle_in.edgeColor1;
     vec4 ec2 = triangle_in.edgeColor2;

     const vec3 dis = vertex_in.dis;
     vec3 hl = vec3(ec0.a, ec1.a, ec2.a);
     vec3 thickness = vec3(max(dis.y, dis.z), max(dis.x, dis.z), max(dis.x, dis.y));
     //thickness = step(fract(8.0*thickness), vec3(0.5));
     vec3 w = fwidth(dis);    // gl_FragCoord.w*fwidth(dis);
     vec3 range = edgeWidth*w*max(max(vec3(squeezeMin), squeezeScale*thickness), hl);
     vec3 shade = smoothstep(0.05*range, range, dis);
     float alpha = min(min(shade.x, shade.y), shade.z);
     //float gamma = min(min(max(shade.y, shade.z), max(shade.x, shade.z)), max(shade.x, shade.y));
     //float alpha = min(gamma, min(min(shade.x, shade.y), shade.z));
     vec3 filt = 1.0 - sign(shade-vec3(alpha));
     //vec3 filt = sign(1.0-shade);
     float beta = (filt.x + filt.y + filt.z);
     vec4 ec = (filt.x*ec0 + filt.y*ec1 + filt.z*ec2) / beta;
     ec.a = 1.0;
     vec4 lmc = illuminate(vertex_in.normal.xyz, light, vec4(mix(ec.rgb, modelColor.rgb, alpha), 1.0));
     color = mix(ec, lmc, alpha);
     //color = mix(mix(lmc, modelColor, 0.7), ec, 1.0-alpha);
     //color = mix(mix(lmc, modelColor, 0.7), ec, 1.0 - alpha);
     //color = vec4(alpha, alpha, alpha, 1.0);
     //color = vec4(mix(vec3(0.2), vec3(1.0), alpha), 1.0);
}
