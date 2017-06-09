// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <happah/Happah.h>
#include <sstream>

#include "happah/graphics/Shader.hpp"

namespace happah {

Shader::Shader(GLuint type, std::string path)
     : m_id(glCreateShader(type)), m_path(std::move(path)), m_type(type) {
     auto source = slurp(m_path);
     auto temp = source.c_str();
     GLint length = source.size();
     glShaderSource(m_id, 1, &temp, &length);
     glCompileShader(m_id);
     GLint status;
     glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
     if(status == GL_FALSE) throw make_error(*this);
}

Shader::~Shader() { glDeleteShader(m_id); }

GLuint Shader::getId() const { return m_id; }

const std::string& Shader::getPath() const { return m_path; }

GLuint Shader::getType() const { return m_type; }

ComputeShader::ComputeShader(std::string path)
     : Shader(GL_COMPUTE_SHADER, std::move(path)) {}

FragmentShader::FragmentShader(std::string path)
     : Shader(GL_FRAGMENT_SHADER, std::move(path)) {}

GeometryShader::GeometryShader(std::string path)
     : Shader(GL_GEOMETRY_SHADER, std::move(path)) {}

TessellationControlShader::TessellationControlShader(std::string path)
     : Shader(GL_TESS_CONTROL_SHADER, std::move(path)) {}

void TessellationControlShader::setInnerTessellationLevel(const std::array<float, 2>& level) { glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, level.data()); }

void TessellationControlShader::setOuterTessellationLevel(const std::array<float, 4>& level) { glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, level.data()); }

TessellationEvaluationShader::TessellationEvaluationShader(std::string path)
     : Shader(GL_TESS_EVALUATION_SHADER, std::move(path)) {}

VertexShader::VertexShader(std::string path)
     : Shader(GL_VERTEX_SHADER, std::move(path)) {}

HighlightLinesFragmentShader::HighlightLinesFragmentShader()
     : FragmentShader("shaders/highlight-lines.f.glsl"), m_bandColor0(5000), m_bandColor1(5001), m_bandWidth(5002), m_beamDirection(5003), m_beamOrigin(5004), m_light(5005) {}

void HighlightLinesFragmentShader::setBandColor0(const hpcolor& color) { m_bandColor0 = color; }

void HighlightLinesFragmentShader::setBandColor1(const hpcolor& color) { m_bandColor1 = color; }

void HighlightLinesFragmentShader::setBandWidth(hpreal width) { m_bandWidth = width; }

void HighlightLinesFragmentShader::setBeam(const Point3D& origin, const Vector3D& direction) {
     m_beamDirection = direction;
     m_beamOrigin = origin;
}

void HighlightLinesFragmentShader::setLight(const Point3D& light) { m_light = light; }

SimpleFragmentShader::SimpleFragmentShader()
     : FragmentShader("shaders/simple.f.glsl"), m_light(5001), m_modelColor(5000) {}

void SimpleFragmentShader::setLight(const Point3D& light) { m_light = light; }

void SimpleFragmentShader::setModelColor(const hpcolor& color) { m_modelColor = color; }

SimpleVertexShader::SimpleVertexShader()
     : VertexShader("shaders/simple.v.glsl"), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

void SimpleVertexShader::setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

void SimpleVertexShader::setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

std::logic_error make_error(const Shader& shader) {
     auto message = std::stringstream();
     message << "Error in shader('";
     message << shader.getPath();
     message << "'):\n";
     message << make_log(shader);
     return std::logic_error(message.str());
}

GeometryShader make_geometry_shader(std::string path) { return { std::move(path) }; }

HighlightLinesFragmentShader make_highlight_lines_fragment_shader() { return {}; }

std::string make_log(const Shader& shader) {
     auto length = GLint(0);
     glGetShaderiv(shader.getId(), GL_INFO_LOG_LENGTH, &length);
     auto log = std::string(length, ' ');
     glGetShaderInfoLog(shader.getId(), length, &length, &log[0]);
     return log;
}

SimpleFragmentShader make_simple_fragment_shader() { return {}; }

SimpleVertexShader make_simple_vertex_shader() { return {}; }

TessellationEvaluationShader make_tessellation_evaluation_shader(std::string path) { return { std::move(path) }; }
     
//Hedwig Amberg - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
     
SolidWireframeFragmentShader::SolidWireframeFragmentShader() : 
     FragmentShader("shaders/solid-wireframe.f.glsl"), m_modelColor(5000),  m_edgeColor(5001), m_edgeWidth(5002),  m_light(5003) {}
void SolidWireframeFragmentShader::setModelColor(const hpcolor& color) { m_modelColor = color; }
void SolidWireframeFragmentShader::setEdgeColor(const hpcolor& color) { m_edgeColor = color; }
void SolidWireframeFragmentShader::setEdgeWidth(hpreal width) { m_edgeWidth = width; }
void SolidWireframeFragmentShader::setLight(const Point3D& light) { m_light = light; }

SolidWireframeFragmentShader make_swf_fragment_shader() { return {}; }

}//namespace happah

