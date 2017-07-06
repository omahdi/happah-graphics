// Copyright 2017
//   Pawel Herman   - Karlsruhe Institute of Technology - pherman@ira.uka.de
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.05 - Pawel Herman     - Initial commit.
// 2017.07 - Hedwig Amberg    - rename new shader version, add old version with original name.

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
     
class EdgeFragmentShader : public Shader {
public:
     EdgeFragmentShader();

     void setEdgeWidth(hpreal width);

     void setLight(const Point3D& light);

     void setModelColor(const hpcolor& color);

private:
     Uniform<hpreal> m_edgeWidth;
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};//WireframeFragmentShader
     
class EdgeVertexShader : public Shader {
public:
     EdgeVertexShader();

     void setModelViewMatrix(const hpmat4x4& matrix);

     void setProjectionMatrix(const hpmat4x4& matrix);

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};//EdgeVertexShader

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

EdgeVertexShader make_edge_vertex_shader();
     
EdgeFragmentShader make_edge_fragment_shader();
     
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
     
}//namespace happah

