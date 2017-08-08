// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

vec4 calc_normal(vec4 v0, vec4 v1, vec4 v2){

     vec3 w0 = v0.xyz / v0.w;
     vec3 w1 = v1.xyz / v1.w;
     vec3 w2 = v2.xyz / v2.w;
     return vec4(normalize(cross(w2 - w1, w0 - w1)), 1.0);
}

vec3 calc_heights(vec4 v0, vec4 v1, vec4 v2){

     float e0 = distance(v0.xyz, v1.xyz);
     float e1 = distance(v1.xyz, v2.xyz);
     float e2 = distance(v2.xyz, v0.xyz);
     float s = 0.5 * (e0 + e1 + e2);
     float t = sqrt(s * (s - e0) * (s - e1) * (s - e2));
     
     //(h0, h1, h2)
     return vec3((2.0 / e0) * t, (2.0 / e1) * t, (2.0 / e2) * t);
}