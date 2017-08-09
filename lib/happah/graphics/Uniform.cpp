// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <glm/gtc/type_ptr.hpp>
#include <happah/Happah.hpp>

#include "happah/graphics/Uniform.hpp"

namespace happah {

template<>
void Uniform<hpuint>::operator=(hpuint value) {
     m_value = value;
     glUniform1ui(m_location, m_value); 
}

template<>
void Uniform<glm::highp_float>::operator=(glm::highp_float value) {
     m_value = value;
     glUniform1d(m_location, m_value); 
}

template<>
void Uniform<glm::mediump_float>::operator=(glm::mediump_float value) {
     m_value = value;
     glUniform1f(m_location, m_value); 
}

template<>
void Uniform<glm::highp_dmat4x4>::operator=(glm::highp_dmat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4dv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::lowp_dmat4x4>::operator=(glm::lowp_dmat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4dv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::mediump_dmat4x4>::operator=(glm::mediump_dmat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4dv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::highp_mat4x4>::operator=(glm::highp_mat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::lowp_mat4x4>::operator=(glm::lowp_mat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::mediump_mat4x4>::operator=(glm::mediump_mat4x4 value) {
     m_value = std::move(value);
     glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::highp_dvec3>::operator=(glm::highp_dvec3 value) {
     m_value = std::move(value);
     glUniform3dv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::lowp_dvec3>::operator=(glm::lowp_dvec3 value) {
     m_value = std::move(value);
     glUniform3dv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::mediump_dvec3>::operator=(glm::mediump_dvec3 value) {
     m_value = std::move(value);
     glUniform3dv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::highp_vec3>::operator=(glm::highp_vec3 value) {
     m_value = std::move(value);
     glUniform3fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::lowp_vec3>::operator=(glm::lowp_vec3 value) {
     m_value = std::move(value);
     glUniform3fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::mediump_vec3>::operator=(glm::mediump_vec3 value) {
     m_value = std::move(value);
     glUniform3fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::highp_dvec4>::operator=(glm::highp_dvec4 value) {
     m_value = std::move(value);
     glUniform4dv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::lowp_dvec4>::operator=(glm::lowp_dvec4 value) {
     m_value = std::move(value);
     glUniform4dv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::mediump_dvec4>::operator=(glm::mediump_dvec4 value) {
     m_value = std::move(value);
     glUniform4dv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::highp_vec4>::operator=(glm::highp_vec4 value) {
     m_value = std::move(value);
     glUniform4fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::lowp_vec4>::operator=(glm::lowp_vec4 value) {
     m_value = std::move(value);
     glUniform4fv(m_location, 1, glm::value_ptr(m_value));
}

template<>
void Uniform<glm::mediump_vec4>::operator=(glm::mediump_vec4 value) {
     m_value = std::move(value);
     glUniform4fv(m_location, 1, glm::value_ptr(m_value));
}

}//namespace happah

