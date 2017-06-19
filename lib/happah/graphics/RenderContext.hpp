// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "happah/graphics/Buffer.hpp"
#include "happah/graphics/glad.h"
#include "happah/graphics/VertexArray.hpp"

namespace happah {

//DECLARATIONS

enum class GeometryType { ARRAY, MESH };

class PatchType {
public:
     static const PatchType LOOP_BOX_SPLINE;
     static const PatchType QUINTIC;
     static const PatchType TRIANGLE;

     PatchType(GLenum id, GLuint size);

     GLenum getId() const;

     GLuint getSize() const;

private:
     GLenum m_id;
     GLuint m_size;

};//PatchType

template<GeometryType>
class RenderContext;

template<>
class RenderContext<GeometryType::ARRAY> {
public:
     RenderContext(const VertexArray& array, const PatchType& type);

     const PatchType& getType() const;

     const VertexArray& getVertexArray() const;

private:
     const VertexArray& m_array;
     const PatchType& m_type;

};//RenderContext<GeometryType::ARRAY>

template<>
class RenderContext<GeometryType::MESH> {
public:
     RenderContext(const VertexArray& array, const Buffer& indices, const PatchType& type);

     const Buffer& getIndices() const;

     const PatchType& getType() const;

     const VertexArray& getVertexArray() const;

private:
     const VertexArray& m_array;
     const Buffer& m_indices;
     const PatchType& m_type;

};//RenderContext<GeometryType::MESH>

RenderContext<GeometryType::ARRAY> make_render_context(const VertexArray& array, const PatchType& type);

RenderContext<GeometryType::MESH> make_render_context(const VertexArray& array, const Buffer& indices, const PatchType& type);

}//namespace happah

