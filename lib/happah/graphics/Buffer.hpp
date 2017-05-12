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

#include "happah/graphics/glad.h"

namespace happah {

//DECLARATIONS

template<class T>
class Buffer;

template<typename T>
void bind(const Buffer<T>& buffer, GLuint index, GLenum target = GL_SHADER_STORAGE_BUFFER);

template<class T>
Buffer<T> make_buffer(const std::vector<T>& ts, GLenum usage = GL_STATIC_DRAW);

Buffer<Point4D> make_buffer(const std::vector<Point3D>& vertices, GLenum usage = GL_STATIC_DRAW);

Buffer<Point4D> make_buffer(const std::vector<VertexP3>& vertices, GLenum usage = GL_STATIC_DRAW);

template<class T, class First, class... Rest>
Buffer<T> make_buffer(First&& first, Rest&&... rest);

template<class T>
void write(const Buffer<T>& buffer, const T* ts, hpuint n, hpuint offset = 0);

//template<class T, class... Arg>
//Buffer<T> make_buffer(Arg&&... args) { return {{make_raw_array(args)...}, GL_STATIC_DRAW}; }

namespace detail {

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

}//namespace detail

template<class T>
class Buffer {
public:
     Buffer(hpuint n, GLenum usage = GL_STATIC_DRAW)
          : m_size(n) {
          glCreateBuffers(1, &m_id);
          allocate(usage);
     }

     Buffer(const T* ts, hpuint n, GLenum usage = GL_STATIC_DRAW) 
          : m_size(n) {
          glCreateBuffers(1, &m_id);
          allocate(usage, ts);
     }

     Buffer(std::initializer_list<std::tuple<const T*, hpuint> > args, GLenum usage = GL_STATIC_DRAW)
          : m_size(0) {
          glCreateBuffers(1, &m_id);
          for(auto& arg : args) m_size += std::get<1>(arg);
          allocate(usage);
          //TODO: more efficient with glMapBuffer?
          auto offset = 0u;
          for(auto& arg : args) {
               const T* ts;
               hpuint n;
               std::tie(ts, n) = arg;
               write(*this, ts, n, offset);
               offset += n;
          }
     }

     ~Buffer() { glDeleteBuffers(1, &m_id); }

     GLuint getId() const { return m_id; }

     hpuint getSize() const { return m_size; }

private:
     GLuint m_id;
     hpuint m_size;

     void allocate(GLenum usage, const T* ts = NULL) { glNamedBufferData(m_id, sizeof(T) * m_size, ts, usage); }

};

//DEFINITIONS

template<typename T>
void bind(const Buffer<T>& buffer, GLuint index, GLenum target) { glBindBufferBase(target, index, buffer.getId()); }

template<class T>
Buffer<T> make_buffer(const std::vector<T>& ts, GLenum usage) { return { ts.data(), (hpuint)ts.size(), usage }; }

template<class T, class First, class... Rest>
Buffer<T> make_buffer(First&& first, Rest&&... rest) { return detail::do_make_buffer<T, First, Rest...>::call(std::forward<First>(first), std::forward<Rest>(rest)...); }

template<class T>
void write(const Buffer<T>& buffer, const T* ts, hpuint n, hpuint offset) { glNamedBufferSubData(buffer.getId(), sizeof(T) * offset, sizeof(T) * n, ts); }

namespace detail {

     template<class T>
     std::tuple<const T*, hpuint> make_raw_array(const std::vector<T>& ts) { return std::make_tuple(ts.data(), ts.size()); }

}//namespace detail

}//namespace happah

