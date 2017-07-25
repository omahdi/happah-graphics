vec4 illuminate(vec3 normal, vec3 light, vec4 color) {
     float ambientCoefficient = 0.4;
     float diffuseCoefficient = max(0.0, dot(normalize(normal), light));
     return vec4((ambientCoefficient + diffuseCoefficient) * color.rgb, color.a);
}

