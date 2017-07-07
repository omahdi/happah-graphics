// Copyright 2017
//   Pawel Herman   - Karlsruhe Institute of Technology - pherman@ira.uka.de
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.05 - Pawel Herman     - Initial commit.
// 2017.07 - Hedwig Amberg    - add new shader for coloring triangles individualy.

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

TessellationControlShader::TessellationControlShader(std::string path)
     : Shader(GL_TESS_CONTROL_SHADER, std::move(path)) {}

void TessellationControlShader::setInnerTessellationLevel(const std::array<float, 2>& level) { glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, level.data()); }

void TessellationControlShader::setOuterTessellationLevel(const std::array<float, 4>& level) { glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, level.data()); }

EdgeFragmentShader::EdgeFragmentShader()
     : Shader(GL_FRAGMENT_SHADER, "shaders/edge.f.glsl"), m_edgeWidth(5000), m_light(5001), m_modelColor(5002) {}

void EdgeFragmentShader::setEdgeWidth(hpreal width) { m_edgeWidth = width; }

void EdgeFragmentShader::setLight(const Point3D& light) { m_light = light; }

void EdgeFragmentShader::setModelColor(const hpcolor& color) { m_modelColor = color; }
     
EdgeVertexShader::EdgeVertexShader()
     : Shader(GL_VERTEX_SHADER, "shaders/edge.v.glsl"), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

void EdgeVertexShader::setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

void EdgeVertexShader::setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }
     
HighlightLinesFragmentShader::HighlightLinesFragmentShader()
     : Shader(GL_FRAGMENT_SHADER, "shaders/highlight-lines.f.glsl"), m_bandColor0(5000), m_bandColor1(5001), m_bandWidth(5002), m_beamDirection(5003), m_beamOrigin(5004), m_light(5005) {}

void HighlightLinesFragmentShader::setBandColor0(const hpcolor& color) { m_bandColor0 = color; }

void HighlightLinesFragmentShader::setBandColor1(const hpcolor& color) { m_bandColor1 = color; }

void HighlightLinesFragmentShader::setBandWidth(hpreal width) { m_bandWidth = width; }

void HighlightLinesFragmentShader::setBeam(const Point3D& origin, const Vector3D& direction) {
     m_beamDirection = direction;
     m_beamOrigin = origin;
}

void HighlightLinesFragmentShader::setLight(const Point3D& light) { m_light = light; }

SimpleFragmentShader::SimpleFragmentShader()
     : Shader(GL_FRAGMENT_SHADER, "shaders/simple.f.glsl"), m_light(5000), m_modelColor(5001) {}

void SimpleFragmentShader::setLight(const Point3D& light) { m_light = light; }

void SimpleFragmentShader::setModelColor(const hpcolor& color) { m_modelColor = color; }

SimpleVertexShader::SimpleVertexShader()
     : Shader(GL_VERTEX_SHADER, "shaders/simple.v.glsl"), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

void SimpleVertexShader::setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

void SimpleVertexShader::setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

SphereImpostorFragmentShader::SphereImpostorFragmentShader()
     : Shader(GL_FRAGMENT_SHADER, "shaders/sphere-impostor.f.glsl"), m_light(5000), m_modelColor(5001), m_projectionMatrix(1001), m_radius(4001) {}

void SphereImpostorFragmentShader::setLight(const Point3D& light) { m_light = light; }

void SphereImpostorFragmentShader::setModelColor(const hpcolor& color) { m_modelColor = color; }

void SphereImpostorFragmentShader::setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

void SphereImpostorFragmentShader::setRadius(hpreal radius) { m_radius = radius; }

SphereImpostorGeometryShader::SphereImpostorGeometryShader()
     : Shader(GL_GEOMETRY_SHADER, "shaders/sphere-impostor.g.glsl"), m_projectionMatrix(1001), m_radius(4001) {}

void SphereImpostorGeometryShader::setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

void SphereImpostorGeometryShader::setRadius(hpreal radius) { m_radius = radius; }

TrianglesFragmentShader::TrianglesFragmentShader()
     : Shader(GL_FRAGMENT_SHADER, "shaders/triangles.f.glsl"), m_light(5000) {}

void TrianglesFragmentShader::setLight(const Point3D& light) { m_light = light; }
     
TrianglesVertexShader::TrianglesVertexShader()
     : Shader(GL_VERTEX_SHADER, "shaders/triangles.v.glsl"), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

void TrianglesVertexShader::setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

void TrianglesVertexShader::setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

WireframeFragmentShader::WireframeFragmentShader()
     : Shader(GL_FRAGMENT_SHADER, "shaders/wireframe.f.glsl"), m_edgeColor(5000), m_edgeWidth(5001), m_light(5002), m_modelColor(5003) {}

void WireframeFragmentShader::setEdgeColor(const hpcolor& color) { m_edgeColor = color; }

void WireframeFragmentShader::setEdgeWidth(hpreal width) { m_edgeWidth = width; }

void WireframeFragmentShader::setLight(const Point3D& light) { m_light = light; }

void WireframeFragmentShader::setModelColor(const hpcolor& color) { m_modelColor = color; }

std::logic_error make_error(const Shader& shader) {
     auto message = std::stringstream();
     message << "Error in shader('";
     message << shader.getPath();
     message << "'):\n";
     message << make_log(shader);
     return std::logic_error(message.str());
}

Shader make_geometry_shader(std::string path) { return { GL_GEOMETRY_SHADER, std::move(path) }; }

EdgeFragmentShader make_edge_fragment_shader() { return {}; }
     
EdgeVertexShader make_edge_vertex_shader() { return {}; }
     
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

SphereImpostorFragmentShader make_sphere_impostor_fragment_shader() { return {}; }

SphereImpostorGeometryShader make_sphere_impostor_geometry_shader() { return {}; }

Shader make_tessellation_evaluation_shader(std::string path) { return { GL_TESS_EVALUATION_SHADER, std::move(path) }; }

TrianglesFragmentShader make_triangles_fragment_shader() { return {}; }
     
TrianglesVertexShader make_triangles_vertex_shader() { return {}; }
     
WireframeFragmentShader make_wireframe_fragment_shader() { return {}; }
     
}//namespace happah

