// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "happah/graphics/glad.h"

namespace happah {

//DECLARATIONS

class DataType {
public:
     static const DataType DOUBLE;
     static const DataType FLOAT;
     static const DataType UNSIGNED_INT;

     DataType(GLenum id, GLuint size)
          : m_id(id), m_size(size) {}

     GLenum getId() const { return m_id; }

     GLuint getSize() const { return m_size; }

private:
     GLenum m_id;
     GLuint m_size;

};//Type

}//namespace happah

