// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/DataType.hpp"

namespace happah {

const DataType DataType::DOUBLE = { GL_DOUBLE, sizeof(GLdouble) };
const DataType DataType::FLOAT = { GL_FLOAT, sizeof(GLfloat) };
const DataType DataType::UNSIGNED_INT = { GL_UNSIGNED_INT, sizeof(GLuint) };

}//namespace happah

