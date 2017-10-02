// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "happah/graphics/Buffer.hpp"
#include "happah/graphics/glad.h"
#include "happah/graphics/Memory.hpp"
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

     auto getId() const { return m_id; }

     auto getSize() const { return m_size; }

private:
     GLenum m_id;
     GLuint m_size;

};//PatchType

template<GeometryType>
class RenderContext;

template<>
class RenderContext<GeometryType::ARRAY> {
public:
     RenderContext(BufferSegment vertices, GLenum mode)
          : m_mode(mode), m_vertices(std::move(vertices)) {}

     auto& getMode() const { return m_mode; }
     
     auto& getVertices() const { return m_vertices; }

private:
     GLenum m_mode;
     BufferSegment m_vertices;

};//RenderContext<GeometryType::ARRAY>

template<>
class RenderContext<GeometryType::MESH> {
public:
     RenderContext(BufferSegment vertices, BufferSegment indices, GLenum mode)
          : m_indices(std::move(indices)), m_mode(mode), m_vertices(std::move(vertices)) {}

     auto& getIndices() const { return m_indices; }

     auto& getMode() const { return m_mode; }

     auto& getVertices() const { return m_vertices; }

private:
     BufferSegment m_indices;
     GLenum m_mode;
     BufferSegment m_vertices;

};//RenderContext<GeometryType::MESH>

inline void activate(const RenderContext<GeometryType::ARRAY>& context, const VertexArray& array, GLuint target) { activate(context.getVertices(), array, target); }

inline void activate(const RenderContext<GeometryType::ARRAY>& context, const VertexArray& array) { activate(context, array, 0); }

inline void activate(const RenderContext<GeometryType::MESH>& context, const VertexArray& array, GLuint target) {
     activate(context.getVertices(), array, target);
     activate(context.getIndices(), array);
}

inline void activate(const RenderContext<GeometryType::MESH>& context, const VertexArray& array) { activate(context, array, 0); }

inline RenderContext<GeometryType::ARRAY> make_render_context(BufferSegment vertices, GLenum mode) { return { std::move(vertices), mode }; }

inline RenderContext<GeometryType::ARRAY> make_render_context(const Buffer& vertices, GLenum mode) { return { make_buffer_segment(vertices), mode }; }

inline RenderContext<GeometryType::MESH> make_render_context(BufferSegment vertices, BufferSegment indices, GLenum mode) { return { std::move(vertices), std::move(indices), mode }; }

inline RenderContext<GeometryType::MESH> make_render_context(const Buffer& vertices, const Buffer& indices, GLenum mode) { return { make_buffer_segment(vertices), make_buffer_segment(indices), mode }; }

template<class Space, hpuint degree>
RenderContext<GeometryType::MESH> make_render_context(Memory& memory, const BezierTriangleMesh<Space, degree>& mesh) {
     auto temp = write(memory, mesh);
     return make_render_context(std::get<0>(temp), std::get<1>(temp), GL_PATCHES);
}

template<class Vertex>
RenderContext<GeometryType::MESH> make_render_context(Memory& memory, const LoopBoxSplineMesh<Vertex>& mesh) {
     auto temp = write(memory, mesh);
     return make_render_context(std::get<0>(temp), std::get<1>(temp), GL_PATCHES);
}

template<class Vertex>
RenderContext<GeometryType::ARRAY> make_render_context(Memory& memory, const TriangleArray<Vertex>& array) { return make_render_context(write(memory, array), GL_TRIANGLES); }

template<class Vertex>
RenderContext<GeometryType::MESH> make_render_context(Memory& memory, const TriangleMesh<Vertex>& mesh) {
     auto temp = write(memory, mesh);
     return make_render_context(std::get<0>(temp), std::get<1>(temp), GL_TRIANGLES);
}

}//namespace happah

