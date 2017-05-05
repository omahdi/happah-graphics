// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.h>
#include <happah/math/Space.h>

#include "happah/graphics/Buffer.hpp"
#include "happah/graphics/glad.h"

namespace happah {

//DECLARATIONS

class Attribute {
public:
     Attribute(GLuint id);

     GLuint getId() const;

     virtual GLuint getSize() const = 0;

private:
     GLuint m_id;

};

class Position : public Attribute {
public:
     Position(GLuint id);

     virtual GLuint getSize() const;

};//class Position

class VertexArray {
public:
     VertexArray();

     ~VertexArray();

     GLuint getId() const;

private:
     GLuint m_id;

};//class VertexArray

void activate(const VertexArray& array);

void bind(const VertexArray& array, const Buffer<Point4D>& vertices, const Buffer<hpuint>& indices);

template<class... Attributes>
VertexArray make_vertex_array(const Attributes&... attributes);

namespace detail {

void describe(const VertexArray& array, GLuint offset, const Position& position);

template<class Attribute, class... Attributes>
void describe(const VertexArray& array, GLuint offset, const Attribute& attribute, const Attributes&... attributes);

}//namespace detail

//DEFINITIONS

template<class... Attributes>
VertexArray make_vertex_array(const Attributes&... attributes) {
     auto array = VertexArray();
     detail::describe(array, 0, attributes...);
     return array;
}

namespace detail {

template<class Attribute, class... Attributes>
void describe(const VertexArray& array, GLuint offset, const Attribute& attribute, const Attributes&... attributes) {
     describe(array, offset, attribute);
     describe(array, offset + attribute.getSize(), attributes...);
}

}

}//namespace happah

