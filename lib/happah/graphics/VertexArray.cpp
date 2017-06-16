// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/VertexArray.hpp"

namespace happah {

Attribute::Attribute(GLuint id, GLint dimension, Type type)
     : m_dimension(dimension), m_id(id), m_type(std::move(type)) {}

GLint Attribute::getDimension() const { return m_dimension; }

GLuint Attribute::getId() const { return m_id; }

GLuint Attribute::getSize() const { return m_dimension * m_type.getSize(); }

Type Attribute::getType() const { return m_type; }

VertexArray::VertexArray() { glCreateVertexArrays(1, &m_id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

GLuint VertexArray::getId() const { return m_id; }

void activate(const VertexArray& array) { glBindVertexArray(array.getId()); }

void activate(const VertexArray& array, const Buffer& indices) { glVertexArrayElementBuffer(array.getId(), indices.getId()); }

void bind(const VertexArray& array, GLuint target, GLuint offset, const Buffer& buffer) { glVertexArrayVertexBuffer(array.getId(), target, buffer.getId(), offset, buffer.getStride() * buffer.getType().getSize()); }

void bind(const VertexArray& array, GLuint target, const Buffer& buffer) { bind(array, target, 0, buffer); }

void bind(const VertexArray& array, const Buffer& buffer) { bind(array, 0, buffer); }

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute) {
     auto id0 = array.getId();
     auto id1 = attribute.getId();
     glEnableVertexArrayAttrib(id0, id1);
     glVertexArrayAttribFormat(id0, id1, attribute.getDimension(), attribute.getType().getId(), GL_FALSE, offset);
     glVertexArrayAttribBinding(id0, id1, target);
}

void describe(const VertexArray& array, GLuint target, const Attribute& attribute) { describe(array, target, 0, attribute); }

Attribute make_attribute(GLuint id, GLint dimension, Type type) { return { id, dimension, type }; }

VertexArray make_vertex_array() { return {}; }

}//namespace happah

