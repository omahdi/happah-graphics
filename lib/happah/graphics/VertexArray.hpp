// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <array>
#include <happah/Happah.h>
#include <happah/math/Space.h>

#include "happah/graphics/Buffer.hpp"
#include "happah/graphics/glad.h"

namespace happah {

//DECLARATIONS

class Type {
public:
     Type(GLenum id, GLuint size);

     GLenum getId() const;

     GLuint getSize() const;

private:
     GLenum m_id;
     GLuint m_size;

};//Type

struct Types {
     static const Type FLOAT;

};//Types

class Attribute {
public:
     Attribute(GLuint id, GLint dimension, Type type);

     GLint getDimension() const;

     GLuint getId() const;

     GLuint getSize() const;

     Type getType() const;

private:
     GLint m_dimension;
     GLuint m_id;
     Type m_type;

};//Attribute

class VertexArray {
public:
     VertexArray();

     ~VertexArray();

     GLuint getId() const;

private:
     GLuint m_id;

};//VertexArray

void activate(const VertexArray& array);

//Bind buffer to target.
template<class T>
void bind(const VertexArray& array, GLuint target, GLuint offset, const Buffer<T>& buffer);

template<class T>
void bind(const VertexArray& array, GLuint target, const Buffer<T>& buffer);

//Bind ith buffer to target + (i - 1).
template<class T, class... U>
void bind(const VertexArray& array, GLuint target, const Buffer<T>& buffer, const Buffer<U>&... buffers);

//Bind ith buffer to (i - 1).
template<class... T>
void bind(const VertexArray& array, const Buffer<T>&... buffers);

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute);

void describe(const VertexArray& array, GLuint target, const Attribute& attribute);

template<class... Attributes>
void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute, const Attributes&... attributes);

Attribute make_attribute(GLuint id, GLint dimension, Type type);

VertexArray make_vertex_array();

//Make interleaved vertex array.
template<class... Attributes>
VertexArray make_vertex_array(const Attributes&... attributes);

//DEFINITIONS

template<class T>
void bind(const VertexArray& array, GLuint target, GLuint offset, const Buffer<T>& buffer) { glVertexArrayVertexBuffer(array.getId(), target, buffer.getId(), offset, sizeof(T)); }

template<class T>
void bind(const VertexArray& array, GLuint target, const Buffer<T>& buffer) { bind(array, target, 0, buffer); }

template<class T, class... U>
void bind(const VertexArray& array, GLuint target, const Buffer<T>& buffer, const Buffer<U>&... buffers) {
     bind(array, target, buffer);
     bind(array, target + 1, buffers...);
}

template<class... T>
void bind(const VertexArray& array, const Buffer<T>&... buffers) { bind(array, 0, buffers...); }

template<class... Attributes>
void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute, const Attributes&... attributes) {
     describe(array, target, offset, attribute);
     describe(array, target, offset + attribute.getSize(), attributes...);
}

template<class... Attributes>
VertexArray make_vertex_array(const Attributes&... attributes) {
     auto array = VertexArray();
     describe(array, 0, 0, attributes...);
     return array;
}

}//namespace happah

