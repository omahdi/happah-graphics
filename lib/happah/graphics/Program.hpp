// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.hpp>
#include <stdexcept>

#include "happah/graphics/RenderContext.hpp"
#include "happah/graphics/Shader.hpp"
#include "happah/graphics/Uniform.hpp"

namespace happah {

class Program {
public:
     Program(std::string name)
           : m_id(glCreateProgram()), m_name(std::move(name)) {}

     virtual ~Program() { glDeleteProgram(m_id); }

     auto& getId() const { return m_id; }

     auto& getName() const { return m_name; }

private:
     GLuint m_id;
     std::string m_name;

};//Program

inline void activate(const Program& program) { glUseProgram(program.getId()); }

void activate(const Program& program, const PatchType& type);

inline void attach(const Program& program, const Shader& shader) { glAttachShader(program.getId(), shader.getId()); }

template<class... Shaders>
void attach(const Program& program, const Shader& shader, const Shaders&... shaders);

template<class... Shaders>
void build(const Program& program, const Shaders&... shaders);

inline void detach(const Program& program, const Shader& shader) { glDetachShader(program.getId(), shader.getId()); }

template<class... Shaders>
void detach(const Program& program, const Shader& shader, const Shaders&... shaders);

void execute(const Program& program, hpuint nx, hpuint ny = 1, hpuint nz = 1);

void execute(const Program& program, const RenderContext<GeometryType::ARRAY>& context);

void execute(const Program& program, const RenderContext<GeometryType::MESH>& context);

void link(const Program& program);

std::logic_error make_error(const Program& program);

std::string make_log(const Program& program);

inline Program make_program(std::string name) { return { std::move(name) }; }

template<class... Shaders>
Program make_program(std::string name, const Shaders&... shaders);

template<typename T>
Uniform<T> make_uniform(const Program& program, std::string name);

inline void render(const Program& program, const RenderContext<GeometryType::ARRAY>& context);

inline void render(const Program& program, const RenderContext<GeometryType::MESH>& context);

//DEFINITIONS

template<class... Shaders>
void attach(const Program& program, const Shader& shader, const Shaders&... shaders) {
     attach(program, shader);
     attach(program, shaders...);
}

template<class... Shaders>
void build(const Program& program, const Shaders&... shaders) {
     attach(program, shaders...);
     link(program);
     detach(program, shaders...);
}

template<class... Shaders>
void detach(const Program& program, const Shader& shader, const Shaders&... shaders) {
     detach(program, shader);
     detach(program, shaders...);
}

template<class... Shaders>
Program make_program(std::string name, const Shaders&... shaders) {
     auto program = make_program(std::move(name));
     build(program, shaders...);
     return program;
}

template<typename T>
Uniform<T> make_uniform(const Program& program, std::string name) {
     auto location = glGetUniformLocation(program.getId(), name.c_str());
     if(location < 0) throw std::logic_error(std::string("Failed to find uniform ") + name + ".");
     return { location };
}

inline void render(const Program& program, const RenderContext<GeometryType::ARRAY>& context) { execute(program, context); }

inline void render(const Program& program, const RenderContext<GeometryType::MESH>& context) { execute(program, context); }

}//namespace happah

