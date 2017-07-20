// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <array>
#include <happah/Happah.hpp>
#include <happah/math/Space.hpp>

#include "happah/graphics/DataType.hpp"
#include "happah/graphics/glad.h"

namespace happah {

//DECLARATIONS

class Attribute {
public:
     Attribute(GLuint id, GLint dimension, const DataType& type);

     GLint getDimension() const;

     GLuint getId() const;

     GLuint getSize() const;

     const DataType& getType() const;

private:
     GLint m_dimension;
     GLuint m_id;
     const DataType& m_type;

};//Attribute

class VertexArray {
public:
     VertexArray();

     ~VertexArray();

     GLuint getId() const;

private:
     GLuint m_id;

};//VertexArray

void activate(const VertexArray& array);

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute);

void describe(const VertexArray& array, GLuint target, const Attribute& attribute);

//Describe interleaved vertex array.
template<class... Attributes>
void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute, const Attributes&... attributes);

Attribute make_attribute(GLuint id, GLint dimension, const DataType& type);

VertexArray make_vertex_array();

//DEFINITIONS

template<class... Attributes>
void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute, const Attributes&... attributes) {
     describe(array, target, offset, attribute);
     describe(array, target, offset + attribute.getSize(), attributes...);
}

}//namespace happah

