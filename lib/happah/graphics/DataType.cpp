// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/DataType.hpp"

namespace happah {

const DataType DataType::FLOAT = { GL_FLOAT, sizeof(GLfloat) };
const DataType DataType::UNSIGNED_INT = { GL_UNSIGNED_INT, sizeof(GLuint) };

DataType::DataType(GLenum id, GLuint size)
     : m_id(id), m_size(size) {}

GLenum DataType::getId() const { return m_id; }

GLuint DataType::getSize() const { return m_size; }

}//namespace happah

