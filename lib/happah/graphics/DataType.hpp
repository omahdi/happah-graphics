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
     static const DataType BOOL;
     static const DataType FLOAT;
     static const DataType INT;
     static const DataType UNSIGNED_INT;

     DataType(GLenum id, GLuint size);

     GLenum getId() const;

     GLuint getSize() const;

private:
     GLenum m_id;
     GLuint m_size;

};//Type

}//namespace happah

