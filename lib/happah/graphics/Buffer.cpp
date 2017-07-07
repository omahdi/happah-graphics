// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/Buffer.hpp"

namespace happah {

Buffer::Buffer(hpuint n, const DataType& type, GLsizei stride, GLenum usage)
     : m_size(n), m_stride(stride), m_type(std::move(type)) {
     glCreateBuffers(1, &m_id);
     glNamedBufferData(m_id, m_size * m_type.getSize(), NULL, usage);
}

Buffer::~Buffer() { glDeleteBuffers(1, &m_id); }

GLuint Buffer::getId() const { return m_id; }

hpuint Buffer::getSize() const { return m_size; }

GLsizei Buffer::getStride() const { return m_stride; }

const DataType& Buffer::getType() const { return m_type; }

void activate(const Buffer& indices, const VertexArray& array) { glVertexArrayElementBuffer(array.getId(), indices.getId()); }

void activate(const Buffer& buffer, const VertexArray& array, GLuint target, GLuint offset) { glVertexArrayVertexBuffer(array.getId(), target, buffer.getId(), offset, buffer.getStride() * buffer.getType().getSize()); }

void activate(const Buffer& buffer, const VertexArray& array, GLuint target) { activate(buffer, array, target, 0); }

void activate(const Buffer& buffer, GLuint target, GLenum type) { glBindBufferBase(type, target, buffer.getId()); }

Buffer make_buffer(hpuint n, const DataType& type, GLsizei stride, GLenum usage) { return { n, type, stride, usage }; }

Buffer make_buffer(const Indices& indices, GLenum usage) {
     auto buffer = make_buffer(indices.size(), DataType::UNSIGNED_INT, 0, usage);
     write(buffer, indices);
     return buffer;
}

Buffer make_buffer(const std::vector<Point4D>& points, GLenum usage) {
     auto buffer = make_buffer(points.size() << 2, DataType::FLOAT, 4, usage);
     write(buffer, points);
     return buffer;
}

Buffer make_buffer(const std::vector<Point3D>& points, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<Point4D>();
     temp.reserve(points.size());
     for(auto& point : points) temp.emplace_back(point, 1.0f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<Point2D>& points, GLenum usage) {
     auto buffer = make_buffer(points.size() << 1, DataType::FLOAT, 2, usage);
     write(buffer, points);
     return buffer;
}

Buffer make_buffer(const std::vector<VertexP3>& vertices, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<Point4D>();
     temp.reserve(vertices.size());
     for(auto& vertex : vertices) temp.emplace_back(vertex.position, 1.0f);
     return make_buffer(temp, usage);
}

hpuint size(const Buffer& buffer) { return buffer.getSize(); }

}//namespace happah

