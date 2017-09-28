// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "happah/graphics/Buffer.hpp"
#include "happah/graphics/glad.h"
#include "happah/graphics/VertexArray.hpp"

namespace happah {

//DEFINITIONS

enum class GeometryType { ARRAY, MESH };

class PatchType {
public:
     static const PatchType LOOP_BOX_SPLINE;
     static const PatchType QUARTIC;
     static const PatchType QUINTIC;
     static const PatchType POINT;
     static const PatchType TRIANGLE;

     PatchType(GLenum id, GLuint size)
          : m_id(id), m_size(size) {}

     GLenum getId() const { return m_id; }

     GLuint getSize() const { return m_size; }

private:
     GLenum m_id;
     GLuint m_size;

};//PatchType

template<GeometryType>
class RenderContext;

template<>
class RenderContext<GeometryType::ARRAY> {
public:
     RenderContext(const VertexArray& array, const PatchType& type)
          : m_array(array), m_type(type) {}

     const PatchType& getType() const { return m_type; }

     const VertexArray& getVertexArray() const { return m_array; }

private:
     const VertexArray& m_array;
     const PatchType& m_type;

};//RenderContext<GeometryType::ARRAY>

template<>
class RenderContext<GeometryType::MESH> {
public:
     RenderContext(const VertexArray& array, const Buffer& indices, const PatchType& type)
          : m_array(array), m_indices(indices), m_type(type) {}

     const Buffer& getIndices() const { return m_indices; }

     const PatchType& getType() const { return m_type; }

     const VertexArray& getVertexArray() const { return m_array; }

private:
     const VertexArray& m_array;
     const Buffer& m_indices;
     const PatchType& m_type;

};//RenderContext<GeometryType::MESH>

inline RenderContext<GeometryType::ARRAY> make_render_context(const VertexArray& array, const PatchType& type) { return { array, type }; }

inline RenderContext<GeometryType::MESH> make_render_context(const VertexArray& array, const Buffer& indices, const PatchType& type) { return { array, indices, type }; }

}//namespace happah

