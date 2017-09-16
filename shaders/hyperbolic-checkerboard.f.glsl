// Copyright 2017
//   Obada Mahdi - Karlsruhe Institute of Technology - omahdi@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#version 430

in Vertex {
     vec4 position;
     vec3 barycentric;
     noperspective vec2 hyp_uv;
};

in Triangle {
     flat vec3 abc2;
     flat vec4 normal;
};

layout(location = 5000) uniform vec4 u_color0;
layout(location = 5001) uniform vec4 u_color1;
layout(location = 5002) uniform vec2 u_period;
layout(location = 5003) uniform vec3 u_light;

out vec4 color;

// "transition zone"
const float c_tr = 0.05;

void main() {
     const float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), u_light));
     const vec3 b2 = vec3(barycentric.x*barycentric.x, barycentric.y*barycentric.y, barycentric.z*barycentric.z);
     // compute distance of point given by barycentric coordinates (u,v,w)
     // from vertices (1,0,0) and (0,0,1), respectively.
     float t0 = 2*barycentric.y*barycentric.z;
     float dist0 = sqrt(dot(vec3(-t0, t0+b2.z, t0+b2.y), abc2));
     float t1 = 2*barycentric.x*barycentric.y;
     float dist1 = sqrt(dot(vec3(t1+b2.y, t1+b2.x, -t1), abc2));
     // TODO

     vec2 co = 2.0*fract(hyp_uv/u_period);
     float alpha = smoothstep(0.5-c_tr, 0.5+c_tr, co.x)*(1.0-smoothstep(1.5-c_tr, 1.5+c_tr, co.x))-0.5;
     float beta = smoothstep(0.5-c_tr, 0.5+c_tr, co.y)*(1.0-smoothstep(1.5-c_tr, 1.5+c_tr, co.y))-0.5;
     float t = 2.0*sqrt(0.25 + alpha*beta);
     vec3 texcolor = t * u_color0.rgb + (1.0 - t) * u_color1.rgb;
     color = vec4((ambientCoefficient + diffuseCoefficient) * texcolor, 1.0);
     //color = vec4(texcolor, 1.0);
}
