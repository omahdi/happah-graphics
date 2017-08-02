// Copyright 2017
//   Pawel Herman   - Karlsruhe Institute of Technology - pherman@ira.uka.de
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.05 - Pawel Herman     - Initial commit.
// 2017.07 - Hedwig Amberg    - Added new shader for coloring triangles individually.
// 2017.08 - Hedwig Amberg    - Refactored make_..._shader functions to use std::filesystem::path.

#pragma once

#include <array>
#include <experimental/filesystem>
#include <happah/Happah.hpp>
#include <happah/math/Space.hpp>
#include <string>

#include "happah/graphics/glad.h"
#include "happah/graphics/Uniform.hpp"

namespace happah {

class Shader {
public:
     Shader(GLuint type, std::string name, std::string source)
          : m_id(glCreateShader(type)), m_name(std::move(name)), m_source(std::move(source)), m_type(type) {}

     ~Shader() { glDeleteShader(m_id); }

     GLuint getId() const { return m_id; }

     const std::string& getName() const { return m_name; }

     const std::string& getSource() const { return m_source; }

     GLuint getType() const { return m_type; }

private:
     GLuint m_id;
     std::string m_name;
     std::string m_source;
     GLuint m_type;

};//Shader

class TessellationControlShader : public Shader {
public:
     inline static void setInnerTessellationLevel(const std::array<float, 2>& level) { glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, level.data()); }

     inline static void setOuterTessellationLevel(const std::array<float, 4>& level) { glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, level.data()); }

};//TessellationControlShader
     
class EdgeFragmentShader : public Shader {
public:
     EdgeFragmentShader()
          : Shader(GL_FRAGMENT_SHADER, "shaders/edge.f.glsl", slurp("shaders/edge.f.glsl")), m_edgeWidth(5000), m_light(5001), m_modelColor(5002) {}

     void setEdgeWidth(hpreal width)  { m_edgeWidth = width; }

     void setLight(const Point3D& light) { m_light = light; }

     void setModelColor(const hpcolor& color)  { m_modelColor = color; }

private:
     Uniform<hpreal> m_edgeWidth;
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};//EdgeFragmentShader
     
class EdgeVertexShader : public Shader {
public:
     EdgeVertexShader() : Shader(GL_VERTEX_SHADER, "shaders/edge.v.glsl", slurp("shaders/edge.v.glsl")), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

     void setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

     void setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};//EdgeVertexShader

class HighlightLinesFragmentShader : public Shader {
public:
     HighlightLinesFragmentShader()
          : Shader(GL_FRAGMENT_SHADER, "shaders/highlight-lines.f.glsl", slurp("shaders/highlight-lines.f.glsl")), m_bandColor0(5000), m_bandColor1(5001), m_bandWidth(5002), m_beamDirection(5003), m_beamOrigin(5004), m_light(5005) {}
     void setBandColor0(const hpcolor& color) { m_bandColor0 = color; }

     void setBandColor1(const hpcolor& color) { m_bandColor1 = color; }

     void setBandWidth(hpreal width) { m_bandWidth = width; }

     void setBeam(const Point3D& origin, const Vector3D& direction);

     void setLight(const Point3D& light)  { m_light = light; }

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
     SimpleFragmentShader()
          : Shader(GL_FRAGMENT_SHADER, "shaders/simple.f.glsl", slurp("shaders/simple.f.glsl")), m_light(5000), m_modelColor(5001) {}

     void setLight(const Point3D& light) { m_light = light; }

     void setModelColor(const hpcolor& color) { m_modelColor = color; }

private:
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};//SimpleFragmentShader

class SimpleVertexShader : public Shader {
public:
     SimpleVertexShader()
          : Shader(GL_VERTEX_SHADER, "shaders/simple.v.glsl", slurp("shaders/simple.v.glsl")), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

     void setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

     void setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};//SimpleVertexShader

class SphereImpostorFragmentShader : public Shader {
public:
     SphereImpostorFragmentShader()
          : Shader(GL_FRAGMENT_SHADER, "shaders/sphere-impostor.f.glsl", slurp("shaders/sphere-impostor.f.glsl")), m_light(5000), m_modelColor(5001), m_projectionMatrix(1001), m_radius(4001) {}

     void setLight(const Point3D& light) { m_light = light; }

     void setModelColor(const hpcolor& color) { m_modelColor = color; }

     void setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

     void setRadius(hpreal radius) { m_radius = radius; }

private:
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;
     Uniform<hpmat4x4> m_projectionMatrix;
     Uniform<hpreal> m_radius;

};//SphereImpostorFragmentShader

class SphereImpostorGeometryShader : public Shader {
public:
     SphereImpostorGeometryShader()
          : Shader(GL_GEOMETRY_SHADER, "shaders/sphere-impostor.g.glsl", slurp("shaders/sphere-impostor.g.glsl")), m_projectionMatrix(1001), m_radius(4001) {}

     void setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

     void setRadius(hpreal radius) { m_radius = radius; }

private:
     Uniform<hpmat4x4> m_projectionMatrix;
     Uniform<hpreal> m_radius;

};//SphereImpostorGeometryShader

class TrianglesFragmentShader : public Shader {
public:
     TrianglesFragmentShader()
          : Shader(GL_FRAGMENT_SHADER, "shaders/triangles.f.glsl", slurp("shaders/triangles.f.glsl")), m_light(5000) {}

     void setLight(const Point3D& light) { m_light = light; }

private:
     Uniform<Point3D> m_light;

};//TrianglesFragmentShader
     
class TrianglesVertexShader : public Shader {
public:
     TrianglesVertexShader()
          : Shader(GL_VERTEX_SHADER, "shaders/triangles.v.glsl", slurp("shaders/triangles.v.glsl")), m_modelViewMatrix(1000), m_projectionMatrix(1001) {}

     void setModelViewMatrix(const hpmat4x4& matrix) { m_modelViewMatrix = matrix; }

     void setProjectionMatrix(const hpmat4x4& matrix) { m_projectionMatrix = matrix; }

private:
     Uniform<hpmat4x4> m_modelViewMatrix;
     Uniform<hpmat4x4> m_projectionMatrix;

};//TrianglesVertexShader

class WireframeFragmentShader : public Shader {
public:
     WireframeFragmentShader()
          : Shader(GL_FRAGMENT_SHADER, "shaders/wireframe.f.glsl", slurp("shaders/wireframe.f.glsl")), m_edgeColor(5000), m_edgeWidth(5001), m_light(5002), m_modelColor(5003) {}

     void setEdgeColor(const hpcolor& color) { m_edgeColor = color; }

     void setEdgeWidth(hpreal width) { m_edgeWidth = width; }

     void setLight(const Point3D& light) { m_light = light; }

     void setModelColor(const hpcolor& color) { m_modelColor = color; }

private:
     Uniform<hpcolor> m_edgeColor;
     Uniform<hpreal> m_edgeWidth;
     Uniform<Point3D> m_light;
     Uniform<hpcolor> m_modelColor;

};//WireframeFragmentShader

void compile(const Shader& shader);

inline void load(const std::string& name, const std::string& source) { glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, name.data(), -1, source.data()); }

inline void load(const std::string& name, const std::experimental::filesystem::path& source) { load(name, slurp(source.string())); }

std::logic_error make_error(const Shader& shader);

std::string make_log(const Shader& shader);

inline EdgeVertexShader make_edge_vertex_shader() { return {}; }

inline EdgeFragmentShader make_edge_fragment_shader() { return {}; }

inline Shader make_geometry_shader(std::string name, std::string source) { return { GL_GEOMETRY_SHADER, std::move(name), std::move(source) }; }

inline Shader make_geometry_shader(const std::experimental::filesystem::path& path) { return { GL_GEOMETRY_SHADER, path.string(), slurp(path) }; }

inline HighlightLinesFragmentShader make_highlight_lines_fragment_shader() { return {}; }

inline SimpleFragmentShader make_simple_fragment_shader() { return {}; }

inline SimpleVertexShader make_simple_vertex_shader() { return {}; }

inline SphereImpostorFragmentShader make_sphere_impostor_fragment_shader() { return {}; }

inline SphereImpostorGeometryShader make_sphere_impostor_geometry_shader() { return {}; }

inline Shader make_tessellation_evaluation_shader(std::string name, std::string source) { return { GL_TESS_EVALUATION_SHADER, std::move(name), std::move(source) }; }

inline Shader make_tessellation_evaluation_shader(const std::experimental::filesystem::path& path) { return { GL_TESS_EVALUATION_SHADER, path.string(), slurp(path) }; }

inline TrianglesVertexShader make_triangles_vertex_shader() { return {}; }

inline TrianglesFragmentShader make_triangles_fragment_shader() { return {}; }

inline WireframeFragmentShader make_wireframe_fragment_shader() { return {}; }

}//namespace happah

