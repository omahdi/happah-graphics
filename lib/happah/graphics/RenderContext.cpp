// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/RenderContext.hpp"

namespace happah {

const PatchType PatchType::LOOP_BOX_SPLINE = { GL_PATCHES, 12 };
const PatchType PatchType::QUARTIC = { GL_PATCHES, 15};
const PatchType PatchType::QUINTIC = { GL_PATCHES, 21 };
const PatchType PatchType::POINT = { GL_POINTS, 1 };
const PatchType PatchType::TRIANGLE = { GL_TRIANGLES, 3 };

}//namespace happah

