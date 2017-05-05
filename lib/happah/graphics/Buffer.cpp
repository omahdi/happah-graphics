// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/Buffer.hpp"

namespace happah {

Buffer<Point4D> make_buffer(const std::vector<VertexP3>& vertices, GLenum usage) {
     auto temp = std::vector<Point4D>();
     temp.reserve(vertices.size());
     for(auto& vertex : vertices) temp.emplace_back(vertex.position, 1.0f);
     return { temp.data(), (unsigned int)temp.size(), usage };
}

}//namespace happah

