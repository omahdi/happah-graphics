// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/VertexArray.hpp"

namespace happah {

constexpr std::array<hpuint, 1> Attribute::SIZE;
constexpr std::array<GLenum, 1> Attribute::TYPE;

Attribute::Attribute(GLuint id, GLint dimension, Type type)
     : m_dimension(dimension), m_id(id), m_type(type) {}

GLint Attribute::getDimension() const { return m_dimension; }

GLuint Attribute::getId() const { return m_id; }

GLuint Attribute::getSize() const { return m_dimension * SIZE[static_cast<int>(m_type)]; }

GLenum Attribute::getType() const { return TYPE[static_cast<int>(m_type)]; }

VertexArray::VertexArray()
     : m_id([]() -> GLuint { GLuint id; glCreateVertexArrays(1, &id); return id; }()) {}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

GLuint VertexArray::getId() const { return m_id; }

void activate(const VertexArray& array) { glBindVertexArray(array.getId()); }

void bind(const VertexArray& array, const Buffer<Point4D>& vertices, const Buffer<hpuint>& indices) {
     glVertexArrayVertexBuffer(array.getId(), 0, vertices.getId(), 0, sizeof(Point4D));
     glVertexArrayElementBuffer(array.getId(), indices.getId());
}

Attribute make_attribute(GLuint id, GLint dimension, Type type) { return { id, dimension, type }; }

VertexArray make_vertex_array() { return {}; }

namespace detail {

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute) {
     auto id0 = array.getId();
     auto id1 = attribute.getId();
     glEnableVertexArrayAttrib(id0, id1);
     glVertexArrayAttribFormat(id0, id1, attribute.getDimension(), attribute.getType(), GL_FALSE, offset);
     glVertexArrayAttribBinding(id0, id1, target);
}

}//namespace detail

}//namespace happah

