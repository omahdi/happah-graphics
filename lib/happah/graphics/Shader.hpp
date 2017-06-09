// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

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

};

class ComputeShader : public Shader {
public:
     ComputeShader(std::string path);

};

class FragmentShader : public Shader {
public:
     FragmentShader(std::string path);

};

class GeometryShader : public Shader {
public:
     GeometryShader(std::string path);

};

class TessellationControlShader : public Shader {
public:
     TessellationControlShader(std::string path);

     static void setInnerTessellationLevel(const std::array<float, 2>& level);

     static void setOuterTessellationLevel(const std::array<float, 4>& level);

};

class TessellationEvaluationShader : public Shader {
public:
     TessellationEvaluationShader(std::string path);

};

class VertexShader : public Shader {
public:
     VertexShader(std::string path);

};

class HighlightLinesFragmentShader : public FragmentShader {
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

};

class SimpleFragmentShader : public FragmentShader {
public:
     SimpleFragmentShader();

     void setLight(const Point3D& light);

     void setModelColor(const hpcolor& color);

private:
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};

class SimpleVertexShader : public VertexShader {
public:
     SimpleVertexShader();

     void setModelViewMatrix(const hpmat4x4& matrix);

     void setProjectionMatrix(const hpmat4x4& matrix);

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};
     
class SolidWireframeFragmentShader : public FragmentShader {
public:
     SolidWireframeFragmentShader();
     void setEdgeColor(const hpcolor& color);
     void setEdgeWidth(hpreal width);
     void setLight(const Point3D& light);
private:
     Uniform<hpcolor> m_edgeColor;
     Uniform<hpreal> m_edgeWidth;
     Uniform<Point3D> m_light;
};
     
SolidWireframeFragmentShader make_swf_fragment_shader();

std::logic_error make_error(const Shader& shader);

GeometryShader make_geometry_shader(std::string path);

HighlightLinesFragmentShader make_highlight_lines_fragment_shader();

std::string make_log(const Shader& shader);

SimpleFragmentShader make_simple_fragment_shader();

SimpleVertexShader make_simple_vertex_shader();

TessellationEvaluationShader make_tessellation_evaluation_shader(std::string path);

}//namespace happah

