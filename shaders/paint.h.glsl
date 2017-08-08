// Copyright 2017
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.08 - Hedwig Amberg    - used new methods from headers in shaders.

//TODO: range auf Pixel beziehen ~2 Pixel antialiasing

vec4 paint_wf(float edgeWidth, vec3 dis, vec4 bgColor, vec4 edgeColor){

     float d = min(dis.x, min(dis.y, dis.z));
     
     float w = 0.5 * edgeWidth;
     float range = 0.1 * w;
     
     float alpha;
     
     if(d <= w - range) alpha = 1.0;
     else if(d <= w + range) {
          float x = (d - w + range) / range; 
          alpha = pow(2.0, -2.0 * x * x);
     } else alpha = 0.0;
     
     return alpha * edgeColor + (1.0 - alpha) * bgColor;
}

vec4 paint_vertex(float edgeWidth, vec3 dis, vec3 maxHeights, vec4 bgColor, vec4 vColor0, vec4 vColor1, vec4 vColor2){

     float w = 0.5 * edgeWidth;
     float range = 0.1 * w;
     
     float vertexRange0 = maxHeights.y - dis.y;
     float vertexRange1 = maxHeights.z - dis.z;
     float vertexRange2 = maxHeights.x - dis.x;
     float vertd = min(vertexRange0, min(vertexRange1, vertexRange2));
     
     vec4 vertexColor = vec4(0,0,0,0);
     
     if(vertexRange0 <= w + range){
          vertexColor = vColor0;
     }else if(vertexRange1 <= w + range){
          vertexColor = vColor1;
     }else if(vertexRange2 <= w + range){
          vertexColor = vColor2;
     }
     
     float beta;
     
     if(vertd <= w - range){
          beta = 1.0;
     } else if(vertd <= w + range) {
          float x = (vertd - w + range) / range; 
          beta = pow(2.0, -2.0 * x * x);
     } else beta = 0.0;
     
     return beta * vertexColor + (1.0 - beta) * bgColor;
}

vec4 paint_edges(float edgeWidth, vec3 dis, vec3 maxHeights, vec4 bgColor, vec4 eColor0, vec4 eColor1, vec4 eColor2, vec4 vColor0, vec4 vColor1, vec4 vColor2) {

     //determine nearest edge
     vec4 color = (dis.y < dis.z) ? ((dis.x < dis.y) ? eColor0 : eColor1) : ((dis.x < dis.z) ? eColor0 : eColor2);

     color = paint_wf(edgeWidth, dis, bgColor, color);
     return paint_vertex(edgeWidth, dis, maxHeights, color, vColor0, vColor1, vColor2);
}
