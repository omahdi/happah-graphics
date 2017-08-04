// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/VertexArray.hpp"

namespace happah {

void describe(const VertexArray& array, GLuint target, GLuint offset, const Attribute& attribute) {
     auto id0 = array.getId();
     auto id1 = attribute.getId();
     glEnableVertexArrayAttrib(id0, id1);
     glVertexArrayAttribFormat(id0, id1, attribute.getDimension(), attribute.getType().getId(), GL_FALSE, offset);
     glVertexArrayAttribBinding(id0, id1, target);
}

}//namespace happah

