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

class Buffer {
public:
     Buffer(hpuint n, const DataType& type, GLsizei stride = 0, GLenum usage = GL_STATIC_DRAW);

     ~Buffer() { glDeleteBuffers(1, &m_id); }

     GLuint getId() const { return m_id; }

     hpuint getSize() const { return m_size; }

     GLsizei getStride() const { return m_stride; }

     const DataType& getType() const { return m_type; }

private:
     GLuint m_id;
     hpuint m_size;
     GLsizei m_stride;
     const DataType& m_type;

};//Buffer

inline void activate(const Buffer& indices, const VertexArray& array) { glVertexArrayElementBuffer(array.getId(), indices.getId()); }

inline void activate(const Buffer& buffer, const VertexArray& array, GLuint target, GLuint offset) { glVertexArrayVertexBuffer(array.getId(), target, buffer.getId(), offset, buffer.getStride() * buffer.getType().getSize()); }
inline void activate(const Buffer& buffer, const VertexArray& array, GLuint target) { activate(buffer, array, target, 0); }

inline void activate(const Buffer& buffer, GLuint target, GLenum type = GL_SHADER_STORAGE_BUFFER)  { glBindBufferBase(type, target, buffer.getId()); }

inline Buffer make_buffer(hpuint n, const DataType& type, GLsizei stride = 0, GLenum usage = GL_STATIC_DRAW) { return { n, type, stride, usage }; }

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

inline hpuint size(const Buffer& buffer) { return buffer.getSize(); }

template<class T>
void write(const Buffer& buffer, const T* ts, hpuint n, hpuint offset = 0);

template<class T>
void write(const Buffer& buffer, const std::vector<T>& ts, hpuint offset = 0);

//DEFINITIONS

template<class T>
void write(const Buffer& buffer, const T* ts, hpuint n, hpuint offset) { glNamedBufferSubData(buffer.getId(), sizeof(T) * offset, sizeof(T) * n, ts); }

template<class T>
void write(const Buffer& buffer, const std::vector<T>& ts, hpuint offset) { write(buffer, ts.data(), ts.size(), offset); }

}//namespace happah

