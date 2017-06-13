// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/VertexArray.hpp"

namespace happah {

Type::Type(GLenum id, GLuint size)
     : m_id(id), m_size(size) {}

GLenum Type::getId() const { return m_id; }

GLuint Type::getSize() const { return m_size; }

const Type Types::FLOAT = { GL_FLOAT, sizeof(GLfloat) };

Attribute::Attribute(GLuint id, GLint dimension, Type type)
     : m_dimension(dimension), m_id(id), m_type(type) {}

GLint Attribute::getDimension() const { return m_dimension; }

GLuint Attribute::getId() const { return m_id; }

GLuint Attribute::getSize() const { return m_dimension * m_type.getSize(); }

Type Attribute::getType() const { return m_type; }

VertexArray::VertexArray()
     : m_id([]() -> GLuint { GLuint id; glCreateVertexArrays(1, &id); return id; }()) {}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

GLuint VertexArray::getId() const { return m_id; }

void activate(const VertexArray& array) { glBindVertexArray(array.getId()); }

void bind(const VertexArray& array, const Buffer<Point4D>& vertices, const Buffer<hpuint>& indices) {
     bind(array, 0, vertices);
     glVertexArrayElementBuffer(array.getId(), indices.getId());
}

Attribute make_attribute(GLuint id, GLint dimension, Type type) { return { id, dimension, type }; }

VertexArray make_vertex_array() { return {}; }

namespace detail {

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute) {
     auto id0 = array.getId();
     auto id1 = attribute.getId();
     glEnableVertexArrayAttrib(id0, id1);
     glVertexArrayAttribFormat(id0, id1, attribute.getDimension(), attribute.getType().getId(), GL_FALSE, offset);
     glVertexArrayAttribBinding(id0, id1, target);
}

}//namespace detail

}//namespace happah

