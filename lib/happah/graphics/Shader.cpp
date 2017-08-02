// Copyright 2017
//   Pawel Herman   - Karlsruhe Institute of Technology - pherman@ira.uka.de
//   Hedwig Amberg  - Karlsruhe Institute of Technology - hedwigdorothea@gmail.com
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

// 2017.05 - Pawel Herman     - Initial commit.
// 2017.07 - Hedwig Amberg    - Added new shader for coloring triangles individually.
// 2017.08 - Hedwig Amberg    - Refactored make_..._shader functions to use std::filesystem::path.

#include <happah/Happah.hpp>
#include <sstream>

#include "happah/graphics/Shader.hpp"

namespace happah {

void HighlightLinesFragmentShader::setBeam(const Point3D& origin, const Vector3D& direction) {
     m_beamDirection = direction;
     m_beamOrigin = origin;
}

void compile(const Shader& shader) {
     auto id = shader.getId();
     auto& source = shader.getSource();
     auto temp = source.c_str();
     auto length = GLint(source.size());
     auto status = GLint();

     glShaderSource(id, 1, &temp, &length);
     glCompileShader(id);
     glGetShaderiv(id, GL_COMPILE_STATUS, &status);
     if(status == GL_FALSE) throw make_error(shader);
}

std::logic_error make_error(const Shader& shader) {
     auto message = std::stringstream();
     message << "Error in shader('";
     message << shader.getName();
     message << "'):\n";
     message << make_log(shader);
     return std::logic_error(message.str());
}

std::string make_log(const Shader& shader) {
     auto length = GLint(0);
     glGetShaderiv(shader.getId(), GL_INFO_LOG_LENGTH, &length);
     auto log = std::string(length, ' ');
     glGetShaderInfoLog(shader.getId(), length, &length, &log[0]);
     return log;
}
     
}//namespace happah

