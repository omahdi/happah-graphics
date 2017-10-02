// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.hpp>
#include <happah/geometry/Vertex.hpp>
#include <happah/math/Space.hpp>
#include <tuple>
#include <vector>

#include "happah/graphics/DataType.hpp"
#include "happah/graphics/glad.h"
#include "happah/graphics/VertexArray.hpp"

namespace happah {

//DECLARATIONS

class Buffer;
class BufferSegment;

inline void activate(const Buffer& indices, const VertexArray& array);

inline void activate(const Buffer& buffer, const VertexArray& array, GLuint target);

inline void activate(const Buffer& buffer, GLuint target, GLenum type = GL_SHADER_STORAGE_BUFFER);

inline void activate(const BufferSegment& indices, const VertexArray& array);

inline void activate(const BufferSegment& segment, const VertexArray& array, GLuint target);

inline Buffer make_buffer(hpuint n, const DataType& type, GLsizei stride = 0, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const Indices& indices, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::highp_dvec3>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::highp_vec3>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::lowp_vec3>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::mediump_vec3>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::highp_dvec4>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::highp_vec4>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::lowp_vec4>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<glm::mediump_vec4>& vecs, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<VertexP2>& vertices, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<VertexP3>& vertices, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<VertexP4>& vertices, GLenum usage = GL_STATIC_DRAW);

inline BufferSegment make_buffer_segment(const Buffer& buffer);

inline hpuint size(const Buffer& buffer);

template<class T>
void write(const Buffer& buffer, const T* ts, hpuint n, hpuint offset = 0);

template<class T>
void write(const Buffer& buffer, const std::vector<T>& ts, hpuint offset = 0);

//DEFINITIONS

class Buffer {
public:
     Buffer(hpuint n, const DataType& type, GLsizei stride = 0, GLenum usage = GL_STATIC_DRAW);

     Buffer(const Buffer& buffer) = default;

     Buffer(Buffer&& buffer)
          : Buffer(buffer) { buffer.m_id = GLuint(0); }

     ~Buffer() { glDeleteBuffers(1, &m_id); }

     auto& getId() const { return m_id; }

     auto& getSize() const { return m_size; }

     auto& getStride() const { return m_stride; }

     auto& getType() const { return m_type; }

private:
     GLuint m_id;
     hpuint m_size;
     GLsizei m_stride;
     const DataType& m_type;

};//Buffer

class BufferSegment {
public:
     BufferSegment(const Buffer& buffer, hpuint size, hpuint offset = 0)
          : m_buffer(buffer), m_offset(offset), m_size(size) {}

     auto& getBuffer() const { return m_buffer; }

     auto& getOffset() const { return m_offset; }

     auto& getSize() const { return m_size; }

private:
     const Buffer& m_buffer;
     hpuint m_offset;
     hpuint m_size;

};//BufferSegment

inline void activate(const Buffer& indices, const VertexArray& array) { glVertexArrayElementBuffer(array.getId(), indices.getId()); }

inline void activate(const Buffer& buffer, const VertexArray& array, GLuint target) { glVertexArrayVertexBuffer(array.getId(), target, buffer.getId(), 0, buffer.getStride() * buffer.getType().getSize()); }

inline void activate(const Buffer& buffer, GLuint target, GLenum type) { glBindBufferBase(type, target, buffer.getId()); }

inline void activate(const BufferSegment& indices, const VertexArray& array) { glVertexArrayElementBuffer(array.getId(), indices.getBuffer().getId()); }

inline void activate(const BufferSegment& segment, const VertexArray& array, GLuint target) {
     auto& buffer = segment.getBuffer();
     auto& type = buffer.getType();
     auto offset = hpuint(segment.getOffset() * type.getSize());
     glVertexArrayVertexBuffer(array.getId(), target, buffer.getId(), offset, buffer.getStride() * type.getSize());
}

inline Buffer make_buffer(hpuint n, const DataType& type, GLsizei stride, GLenum usage) { return { n, type, stride, usage }; }

inline BufferSegment make_buffer_segment(const Buffer& buffer) { return { buffer, buffer.getSize() }; }

inline hpuint size(const Buffer& buffer) { return buffer.getSize(); }

template<class T>
void write(const Buffer& buffer, const T* ts, hpuint n, hpuint offset) { glNamedBufferSubData(buffer.getId(), sizeof(T) * offset, sizeof(T) * n, ts); }

template<class T>
void write(const Buffer& buffer, const std::vector<T>& ts, hpuint offset) { write(buffer, ts.data(), ts.size(), offset); }

}//namespace happah

