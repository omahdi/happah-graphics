// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <glm/gtc/type_ptr.hpp>
#include <happah/Happah.h>

#include "happah/graphics/Uniform.hpp"

namespace happah {

template<>
void Uniform<hpuint>::operator=(hpuint value) {
     m_value = value;
     glUniform1ui(m_location, m_value); 
}

template<>
void Uniform<hpreal>::operator=(hpreal value) {
     m_value = value;
     glUniform1f(m_location, m_value); 
}

template<>
void Uniform<hpmat4x4>::operator=(hpmat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<hpvec2>::operator=(hpvec2 value) {
     m_value = std::move(value);
     glUniform2fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<hpvec3>::operator=(hpvec3 value) {
     m_value = std::move(value);
     glUniform3fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<hpvec4>::operator=(hpvec4 value) {
     m_value = std::move(value);
     glUniform4fv(m_location, 1, glm::value_ptr(m_value));
}

}//namespace happah

