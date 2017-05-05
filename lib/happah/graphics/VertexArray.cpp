// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/VertexArray.hpp"

namespace happah {

Attribute::Attribute(GLuint id)
     : m_id(id) {}

GLuint Attribute::getId() const { return m_id; }

Position::Position(GLuint id)
     : Attribute(id) {}

GLuint Position::getSize() const { return 4 * sizeof(GL_FLOAT); }

VertexArray::VertexArray()
     : m_id([]() -> GLuint { GLuint id; glCreateVertexArrays(1, &id); return id; }()) {}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

GLuint VertexArray::getId() const { return m_id; }

void activate(const VertexArray& array) { glBindVertexArray(array.getId()); }

void bind(const VertexArray& array, const Buffer<Point4D>& vertices, const Buffer<hpuint>& indices) {
     glVertexArrayVertexBuffer(array.getId(), 0, vertices.getId(), 0, sizeof(Point4D));
     glVertexArrayElementBuffer(array.getId(), indices.getId());
}

namespace detail {

void describe(const VertexArray& array, GLuint offset, const Position& position) {
     auto id0 = array.getId();
     auto id1 = position.getId();
     glEnableVertexArrayAttrib(id0, id1);
     glVertexArrayAttribFormat(id0, id1, 3, GL_FLOAT, GL_FALSE, offset);
     glVertexArrayAttribBinding(id0, id1, 0);
}

}//namespace detail

}//namespace happah

