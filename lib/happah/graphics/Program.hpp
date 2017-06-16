// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.h>
#include <stdexcept>

#include "happah/graphics/Shader.hpp"
#include "happah/graphics/Uniform.hpp"
#include "happah/graphics/VertexArray.hpp"

namespace happah {

//DECLARATIONS

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

class ComputeProgram : public Program {
public:
     ComputeProgram(std::string name);

};//ComputeProgram

class RenderProgram : public Program {
public:
     RenderProgram(std::string name, GLenum mode, GLsizei patchSize);

     GLenum getMode() const;

     GLsizei getPatchSize() const;

private:
     GLenum m_mode;
     GLsizei m_patchSize;

};//RenderProgram

void activate(const ComputeProgram& program);

void activate(const RenderProgram& program);

void execute(const ComputeProgram& program, hpuint nx, hpuint ny = 1, hpuint nz = 1);

void execute(const RenderProgram& program, hpuint n, hpuint offset = 0);

std::logic_error make_error(const Program& program);

std::string make_log(const Program& program);

ComputeProgram make_compute_program(std::string name, const Shader& shader);

template<class... Shaders>
RenderProgram make_patches_program(std::string name, int patchSize, const Shaders&... shaders);

template<class... Shaders>
RenderProgram make_triangles_program(std::string name, const Shaders&... shaders);

template<typename T>
Uniform<T> make_uniform(const Program& program, std::string name);

//template<class... T>
//void render(const RenderProgram& program, VertexArray& array, const Buffer<hpuint>& indices, const Buffer<T>&... vertices);

namespace detail {

void link(const Program& program);

void attach(const Program& program, const Shader& shader);

template<class... Shaders>
void attach(const Program& program, const Shader& shader, const Shaders&... shaders);

template<class... Shaders>
void build_program(const Program& program, const Shaders&... shaders);

void detach(const Program& program, const Shader& shader);

template<class... Shaders>
void detach(const Program& program, const Shader& shader, const Shaders&... shaders);

template<class... Shaders>
RenderProgram make_program(std::string name, GLenum mode, int patchSize, const Shaders&... shaders);

}//namespace detail

//DEFINITIONS

template<class... Shaders>
RenderProgram make_patches_program(std::string name, int patchSize, const Shaders&... shaders) { return detail::make_program(std::move(name), GL_PATCHES, patchSize, shaders...); }

template<class... Shaders>
RenderProgram make_triangles_program(std::string name, const Shaders&... shaders) { return detail::make_program(std::move(name), GL_TRIANGLES, 3, shaders...); }

template<typename T>
Uniform<T> make_uniform(const Program& program, std::string name) {
     auto location = glGetUniformLocation(program.getId(), name.c_str());
     if(location < 0) throw std::logic_error(std::string("Failed to find uniform ") + name + ".");
     return { location };
}

/*template<class... T>
void render(const RenderProgram& program, VertexArray& array, const Buffer<hpuint>& indices, const Buffer<T>&... vertices) {
     bind(array, vertices...);
     glVertexArrayElementBuffer(array.getId(), indices.getId());
     execute(program, indices.getSize() / program.getPatchSize());
}*/

namespace detail {

template<class... Shaders>
void attach(const Program& program, const Shader& shader, const Shaders&... shaders) {
     attach(program, shader);
     attach(program, shaders...);
}

template<class... Shaders>
void build_program(const Program& program, const Shaders&... shaders) {
     detail::attach(program, shaders...);
     detail::link(program);
     detail::detach(program, shaders...);
}

template<class... Shaders>
void detach(const Program& program, const Shader& shader, const Shaders&... shaders) {
     detach(program, shader);
     detach(program, shaders...);
}

template<class... Shaders>
RenderProgram make_program(std::string name, GLenum mode, int patchSize, const Shaders&... shaders) {
     auto program = RenderProgram(std::move(name), mode, patchSize);
     build_program(program, shaders...);
     return program;
}

}//namespace detail

}//namespace happah

