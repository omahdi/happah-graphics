// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.07 - Hedwig Amberg    - add new shader for coloring triangles individualy.

#version 430

in Vertex {
     vec4 normal;
     vec4 position;
     vec4 cornerColor;
};

layout(location = 5000) uniform vec3 light;

out vec4 color;

void main() {
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal.xyz), light));
     color = vec4((ambientCoefficient + diffuseCoefficient) * cornerColor.rgb, cornerColor.a);
}

