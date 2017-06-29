// Copyright 2017
//   Pawel Herman   - Karlsruhe Institute of Technology - pherman@ira.uka.de
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.06 - Hedwig Amberg    - Added wireframe fragment shader.
// 2017.05 - Pawel Herman     - Initial commit.

#pragma once

#include <array>
#include <happah/Happah.h>
#include <happah/math/Space.h>
#include <string>

#include "happah/graphics/glad.h"
#include "happah/graphics/Uniform.hpp"

namespace happah {

class Shader {
public:
     Shader(GLuint type, std::string path);

     ~Shader();

     GLuint getId() const;

     const std::string& getPath() const;

     GLuint getType() const;

private:
     GLuint m_id;
     std::string m_path;
     GLuint m_type;

};//Shader

class TessellationControlShader : public Shader {
public:
     TessellationControlShader(std::string path);

     static void setInnerTessellationLevel(const std::array<float, 2>& level);

     static void setOuterTessellationLevel(const std::array<float, 4>& level);

};//TessellationControlShader

class HighlightLinesFragmentShader : public Shader {
public:
     HighlightLinesFragmentShader();

     void setBandColor0(const hpcolor& color);

     void setBandColor1(const hpcolor& color);

     void setBandWidth(hpreal width);

     void setBeam(const Point3D& origin, const Vector3D& direction);

     void setLight(const Point3D& light);

private:
     Uniform<hpcolor> m_bandColor0;
     Uniform<hpcolor> m_bandColor1;
     Uniform<hpreal> m_bandWidth;
     Uniform<Vector3D> m_beamDirection;
     Uniform<Point3D> m_beamOrigin;
     Uniform<Point3D> m_light;

};//HighlightLinesFragmentShader

class SimpleFragmentShader : public Shader {
public:
     SimpleFragmentShader();

     void setLight(const Point3D& light);

     void setModelColor(const hpcolor& color);

private:
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};//SimpleFragmentShader

class SimpleVertexShader : public Shader {
public:
     SimpleVertexShader();

     void setModelViewMatrix(const hpmat4x4& matrix);

     void setProjectionMatrix(const hpmat4x4& matrix);

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};//SimpleVertexShader

class SphereImpostorFragmentShader : public Shader {
public:
     SphereImpostorFragmentShader();

     void setLight(const Point3D& light);

     void setModelColor(const hpcolor& color);

     void setProjectionMatrix(const hpmat4x4& matrix);

     void setRadius(hpreal radius);

private:
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;
     Uniform<hpmat4x4> m_projectionMatrix;
     Uniform<hpreal> m_radius;

};//SphereImpostorFragmentShader

class SphereImpostorGeometryShader : public Shader {
public:
     SphereImpostorGeometryShader();

     void setProjectionMatrix(const hpmat4x4& matrix);

     void setRadius(hpreal radius);

private:
     Uniform<hpmat4x4> m_projectionMatrix;
     Uniform<hpreal> m_radius;

};//SphereImpostorGeometryShader

class WireframeFragmentShader : public Shader {
public:
     WireframeFragmentShader();

     void setEdgeColor(const hpcolor& color);

     void setEdgeWidth(hpreal width);

     void setLight(const Point3D& light);

     void setModelColor(const hpcolor& color);

private:
     Uniform<hpcolor> m_edgeColor;
     Uniform<hpreal> m_edgeWidth;
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};//WireframeFragmentShader
     
class WireframeVertexShader : public Shader {
public:
     WireframeVertexShader();

     void setModelViewMatrix(const hpmat4x4& matrix);

     void setProjectionMatrix(const hpmat4x4& matrix);

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};//SimpleVertexShader

class CheckerboardFragmentShader : public Shader {
public:
     CheckerboardFragmentShader() : Shader(GL_FRAGMENT_SHADER, "shaders/checkerboard.f.glsl") { }
     ~CheckerboardFragmentShader() { }

     void setColors(hpcolor a, hpcolor b) {
          m_color0 = a;
          m_color1 = b;
     }

     void setPeriod(hpvec2 d) {
          m_period = d;
     }

     void setLight(const Point3D& light) {
          m_light = light;
     }

private:
     Uniform<hpcolor> m_color0    {5000};
     Uniform<hpcolor> m_color1    {5001};
     Uniform<hpvec2> m_period     {5002};
     Uniform<Point3D> m_light     {5003};
};//CheckerboardFragmentShader

class CheckerboardGeometryShader : public Shader {
public:
     CheckerboardGeometryShader() : Shader(GL_GEOMETRY_SHADER, "shaders/checkerboard.g.glsl") { }
     ~CheckerboardGeometryShader() { }

     void set_values() const { }
};//CheckerboardGeometryShader

class CheckerboardVertexShader : public Shader {
public:
     CheckerboardVertexShader() : Shader(GL_VERTEX_SHADER, "shaders/checkerboard.v.glsl") { }
     ~CheckerboardVertexShader() { }

     void setModelViewMatrix(hpmat4x4 matrix) {
          m_modelViewMatrix = matrix;
     }

     void setProjectionMatrix(hpmat4x4 matrix) {
          m_projectionMatrix = matrix;
     }

private:
     Uniform<hpmat4x4> m_modelViewMatrix  {1000};
     Uniform<hpmat4x4> m_projectionMatrix {1001};
};//CheckerboardVertexShader

CheckerboardFragmentShader make_checkerboard_fragment_shader();

CheckerboardGeometryShader make_checkerboard_geometry_shader();

CheckerboardVertexShader make_checkerboard_vertex_shader();

std::logic_error make_error(const Shader& shader);

Shader make_geometry_shader(std::string path);

HighlightLinesFragmentShader make_highlight_lines_fragment_shader();

std::string make_log(const Shader& shader);

SimpleFragmentShader make_simple_fragment_shader();

SimpleVertexShader make_simple_vertex_shader();

SphereImpostorFragmentShader make_sphere_impostor_fragment_shader();

SphereImpostorGeometryShader make_sphere_impostor_geometry_shader();

Shader make_tessellation_evaluation_shader(std::string path);

WireframeFragmentShader make_wireframe_fragment_shader();
     
WireframeVertexShader make_wireframe_vertex_shader();
     
}//namespace happah

