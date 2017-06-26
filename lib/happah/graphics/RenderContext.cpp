// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/RenderContext.hpp"

namespace happah {

const PatchType PatchType::LOOP_BOX_SPLINE = { GL_PATCHES, 12 };
const PatchType PatchType::QUINTIC = { GL_PATCHES, 21 };
const PatchType PatchType::POINT = { GL_POINTS, 1 };
const PatchType PatchType::TRIANGLE = { GL_TRIANGLES, 3 };

PatchType::PatchType(GLenum id, GLuint size)
     : m_id(id), m_size(size) {}

GLenum PatchType::getId() const { return m_id; }

GLuint PatchType::getSize() const { return m_size; }

RenderContext<GeometryType::ARRAY>::RenderContext(const VertexArray& array, const PatchType& type)
     : m_array(array), m_type(type) {}

const PatchType& RenderContext<GeometryType::ARRAY>::getType() const { return m_type; }

const VertexArray& RenderContext<GeometryType::ARRAY>::getVertexArray() const { return m_array; }

RenderContext<GeometryType::MESH>::RenderContext(const VertexArray& array, const Buffer& indices, const PatchType& type)
     : m_array(array), m_indices(indices), m_type(type) {}

const Buffer& RenderContext<GeometryType::MESH>::getIndices() const { return m_indices; }

const PatchType& RenderContext<GeometryType::MESH>::getType() const { return m_type; }

const VertexArray& RenderContext<GeometryType::MESH>::getVertexArray() const { return m_array; }

RenderContext<GeometryType::ARRAY> make_render_context(const VertexArray& array, const PatchType& type) { return { array, type }; }

RenderContext<GeometryType::MESH> make_render_context(const VertexArray& array, const Buffer& indices, const PatchType& type) { return { array, indices, type }; }

}//namespace happah

