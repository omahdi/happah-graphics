// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.h>
#include <happah/geometries/LoopBoxSplineMesh.h>
#include <happah/geometries/SurfaceSplineBEZ.h>
#include <happah/geometries/TriangleMesh.h>
#include <happah/math/Space.h>
#include <vector>

#include "happah/graphics/Buffer.hpp"

namespace happah {

class RenderContext {
public:
     template<class Vertex>
     RenderContext(const std::vector<Vertex>& vertices, const Indices& indices)
          : m_indices(make_buffer(indices)), m_vertices(make_buffer(vertices)) {}

     RenderContext(hpuint nVertices, const Indices& indices);

     const Buffer<hpuint>& getIndices() const;

     const Buffer<Point4D>& getVertices() const;

private:
     Buffer<hpuint> m_indices;
     Buffer<Point4D> m_vertices;

};//RenderContext

template<class Vertex>
RenderContext make_render_context(const LoopBoxSplineMesh<Vertex>& mesh) { return { mesh.getControlPoints(), mesh.getIndices() }; }
 
template<class Vertex>
RenderContext make_render_context(const TriangleMesh<Vertex>& mesh) { return { mesh.getVertices(), mesh.getIndices() }; }

template<class Space, hpuint degree>
RenderContext make_render_context(const SurfaceSplineBEZ<Space, degree>& surface) {
     auto patches = surface.getPatches();
     return { std::get<0>(patches), std::get<1>(patches) };
}

}//namespace happah

