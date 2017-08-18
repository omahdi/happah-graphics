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

//DEFINITIONS

class Attribute {
public:
     Attribute(GLuint id, GLint dimension, const DataType& type)
     : m_dimension(dimension), m_id(id), m_type(std::move(type)) {}

     GLint getDimension() const { return m_dimension; }

     GLuint getId() const { return m_id; }

     GLuint getSize() const { return m_dimension * m_type.getSize(); }

     const DataType& getType() const { return m_type; }

private:
     GLint m_dimension;
     GLuint m_id;
     const DataType& m_type;

};//Attribute

class VertexArray {
public:
     VertexArray() { glCreateVertexArrays(1, &m_id); }

     ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

     GLuint getId() const { return m_id; }

private:
     GLuint m_id;

};//VertexArray

inline void activate(const VertexArray& array) { glBindVertexArray(array.getId()); }

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute);

inline void describe(const VertexArray& array, GLuint target, const Attribute& attribute) { describe(array, target, 0, attribute); }

//Describe interleaved vertex array.
template<class... Attributes>
void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute, const Attributes&... attributes);

inline Attribute make_attribute(GLuint id, GLint dimension, const DataType& type) { return { id, dimension, type }; }

inline VertexArray make_vertex_array() { return {}; }

//DEFINITIONS

template<class... Attributes>
void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute, const Attributes&... attributes) {
     describe(array, target, offset, attribute);
     describe(array, target, offset + attribute.getSize(), attributes...);
}

}//namespace happah

