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
#include "happah/graphics/VertexArray.hpp"

namespace happah {

class Program {
public:
     Program(std::string name);

     virtual ~Program();

     GLuint getId() const;

     const std::string& getName() const;

private:
     GLuint m_id;
     std::string m_name;

};//Program

void activate(const Program& program);

void activate(const Program& program, const PatchType& type);

void attach(const Program& program, const Shader& shader);

template<class... Shaders>
void attach(const Program& program, const Shader& shader, const Shaders&... shaders);

template<class... Shaders>
void build(const Program& program, const Shaders&... shaders);

void detach(const Program& program, const Shader& shader);

template<class... Shaders>
void detach(const Program& program, const Shader& shader, const Shaders&... shaders);

void execute(const Program& program, hpuint nx, hpuint ny = 1, hpuint nz = 1);

void execute(const Program& program, const RenderContext<GeometryType::ARRAY>& context, hpuint n, hpuint offset = 0);

void execute(const Program& program, const RenderContext<GeometryType::MESH>& context, hpuint n, hpuint offset = 0);

void link(const Program& program);

std::logic_error make_error(const Program& program);

std::string make_log(const Program& program);

Program make_program(std::string name);

template<class... Shaders>
Program make_program(std::string name, const Shaders&... shaders);

template<typename T>
Uniform<T> make_uniform(const Program& program, std::string name);

void render(const Program& program, const RenderContext<GeometryType::ARRAY>& context, hpuint n, hpuint offset = 0);

void render(const Program& program, const RenderContext<GeometryType::MESH>& context, hpuint n, hpuint offset = 0);

void render(const Program& program, const RenderContext<GeometryType::MESH>& context);

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

}//namespace happah

