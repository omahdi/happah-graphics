// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "happah/graphics/glad.h"

namespace happah {

template<typename T>
class Uniform {
public:
     Uniform(GLint location)
          : m_location(location) {}

     void operator=(T value);

     operator T() const { return m_value; }

protected:
     GLint m_location;
     T m_value;

};

}//namespace happah

