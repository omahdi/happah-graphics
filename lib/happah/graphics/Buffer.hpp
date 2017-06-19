// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.h>
#include <happah/geometries/Vertex.h>
#include <happah/math/Space.h>
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

     ~Buffer();

     GLuint getId() const;

     hpuint getSize() const;

     GLsizei getStride() const;

     const DataType& getType() const;

private:
     GLuint m_id;
     hpuint m_size;
     GLsizei m_stride;
     const DataType& m_type;

};//Buffer

void activate(const Buffer& indices, const VertexArray& array);

void activate(const Buffer& buffer, const VertexArray& array, GLuint target, GLuint offset);

void activate(const Buffer& buffer, const VertexArray& array, GLuint target);

void activate(const Buffer& buffer, GLuint target, GLenum type = GL_SHADER_STORAGE_BUFFER);

//template<class T>
//Buffer make_buffer(std::initializer_list<std::tuple<const T*, hpuint> > args, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(hpuint n, const DataType& type, GLsizei stride = 0, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const Indices& indices, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<Point4D>& points, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<Point3D>& points, GLenum usage = GL_STATIC_DRAW);

Buffer make_buffer(const std::vector<VertexP3>& vertices, GLenum usage = GL_STATIC_DRAW);

//template<class T, class First, class... Rest>
//Buffer<T> make_buffer(First&& first, Rest&&... rest);

hpuint size(const Buffer& buffer);

template<class T>
void write(const Buffer& buffer, const T* ts, hpuint n, hpuint offset = 0);

template<class T>
void write(const Buffer& buffer, const std::vector<T>& ts, hpuint offset = 0);

//template<class T, class... Arg>
//Buffer<T> make_buffer(Arg&&... args) { return {{make_raw_array(args)...}, GL_STATIC_DRAW}; }

/*namespace detail {

     template<class T>
     std::tuple<const T*, hpuint> make_raw_array(const std::vector<T>& ts);

     template<class T, class First, class... Arg>
     struct do_make_buffer {
          static Buffer<T> call(First&& first, Arg&&... args) { return {{make_raw_array(first), make_raw_array(args)...}, GL_STATIC_DRAW}; }
     };

     template<class T, class... Arg>
     struct do_make_buffer<T, int, Arg...> {
          static Buffer<T> call(GLenum usage, Arg&&... args) { return {{make_raw_array(args)...}, usage}; }
     };

}//namespace detail*/

//DEFINITIONS

/*template<class T>
Buffer make_buffer(std::initializer_list<std::tuple<const T*, hpuint> > args, GLenum usage = GL_STATIC_DRAW) {
     auto n = 0u;
     for(auto& arg : args) n += std::get<1>(arg);
     //TODO: more efficient with glMapBuffer?
     auto offset = 0u;
     for(auto& arg : args) {
          const T* ts;
          hpuint n;
          std::tie(ts, n) = arg;
          write(*this, ts, n, offset);
          offset += n;
     }

}*/

//template<class T, class First, class... Rest>
//Buffer<T> make_buffer(First&& first, Rest&&... rest) { return detail::do_make_buffer<T, First, Rest...>::call(std::forward<First>(first), std::forward<Rest>(rest)...); }

template<class T>
void write(const Buffer& buffer, const T* ts, hpuint n, hpuint offset) { glNamedBufferSubData(buffer.getId(), sizeof(T) * offset, sizeof(T) * n, ts); }

template<class T>
void write(const Buffer& buffer, const std::vector<T>& ts, hpuint offset) { write(buffer, ts.data(), ts.size(), offset); }

/*namespace detail {

     template<class T>
     std::tuple<const T*, hpuint> make_raw_array(const std::vector<T>& ts) { return std::make_tuple(ts.data(), ts.size()); }

}//namespace detail*/

}//namespace happah

