// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/DataType.hpp"

namespace happah {

Type::Type(GLenum id, GLuint size)
     : m_id(id), m_size(size) {}

GLenum Type::getId() const { return m_id; }

GLuint Type::getSize() const { return m_size; }

const Type Types::FLOAT = { GL_FLOAT, sizeof(GLfloat) };

const Type Types::UNSIGNED_INT = { GL_UNSIGNED_INT, sizeof(GLuint) };

}//namespace happah

