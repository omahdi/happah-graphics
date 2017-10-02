// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <set>

#include "happah/geometry/BezierTriangleMesh.hpp"
#include "happah/geometry/LoopBoxSplineMesh.hpp"
#include "happah/geometry/TriangleArray.hpp"
#include "happah/geometry/TriangleMesh.hpp"
#include "happah/graphics/Buffer.hpp"

namespace happah {

//DECLARATIONS

class Memory;

//DEFINITIONS

class Memory {
     struct BufferComparator {
          bool operator()(const Buffer& buffer0, const Buffer& buffer1) { return buffer0.getId() < buffer1.getId(); }
     };

public:
     auto& insert(Buffer&& buffer) { return *m_buffers.insert(std::move(buffer)).first; }

private:
     std::set<Buffer, BufferComparator> m_buffers;

};//Memory

template<class Space, hpuint degree>
std::tuple<const Buffer&, const Buffer&> write(Memory& memory, const BezierTriangleMesh<Space, degree>& mesh) {
     auto& controlPoints = memory.insert(make_buffer(mesh.getControlPoints()));
     auto& indices = memory.insert(make_buffer(std::get<1>(mesh.getPatches())));
     return std::tie(controlPoints, indices);
}

template<class Vertex>
std::tuple<const Buffer&, const Buffer&> write(Memory& memory, const LoopBoxSplineMesh<Vertex>& mesh) {
     auto& controlPoints = memory.insert(make_buffer(mesh.getControlPoints()));
     auto& indices = memory.insert(make_buffer(mesh.getIndices()));
     return std::tie(controlPoints, indices);
}

template<class Vertex>
const Buffer& write(Memory& memory, const TriangleArray<Vertex>& array) { return memory.insert(make_buffer(array.getVertices())); }

template<class Vertex>
std::tuple<const Buffer&, const Buffer&> write(Memory& memory, const TriangleMesh<Vertex>& mesh) {
     auto& vertices = memory.insert(make_buffer(mesh.getVertices()));
     auto& indices = memory.insert(make_buffer(mesh.getIndices()));
     return std::tie(vertices, indices);
}

}//namespace happah

