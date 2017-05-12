// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/RenderContext.hpp"

namespace happah {

RenderContext::RenderContext(hpuint nVertices, const Indices& indices)
     : m_indices(make_buffer(indices)), m_vertices(nVertices) {}

const Buffer<hpuint>& RenderContext::getIndices() const { return m_indices; }

const Buffer<Point4D>& RenderContext::getVertices() const { return m_vertices; }

}//namespace happah
