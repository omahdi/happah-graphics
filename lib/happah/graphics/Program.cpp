// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>

#include "happah/graphics/Program.hpp"

namespace happah {

Program::Program(std::string name)
     : m_id(glCreateProgram()), m_name(std::move(name)) {}

Program::~Program() { glDeleteProgram(m_id); }

GLuint Program::getId() const { return m_id; }

const std::string& Program::getName() const { return m_name; }

ComputeProgram::ComputeProgram(std::string name)
     : Program(std::move(name)) {}

RenderProgram::RenderProgram(std::string name, GLenum mode, GLsizei patchSize)
     : Program(std::move(name)), m_mode(mode), m_patchSize(patchSize) {}

GLenum RenderProgram::getMode() const { return m_mode; }

GLsizei RenderProgram::getPatchSize() const { return m_patchSize; }

void activate(const ComputeProgram& program) { glUseProgram(program.getId()); }

void activate(const RenderProgram& program) {
     glUseProgram(program.getId());
     glPatchParameteri(GL_PATCH_VERTICES, program.getPatchSize());
}

void execute(const ComputeProgram& program, hpuint nx, hpuint ny, hpuint nz) {
     glDispatchCompute(nx, ny, nz);
     assert(glGetError() == GL_NO_ERROR);
}

void execute(const RenderProgram& program, hpuint n, hpuint offset) {
     offset *= program.getPatchSize() * sizeof(hpuint);
     glDrawElements(program.getMode(), program.getPatchSize() * n, GL_UNSIGNED_INT, reinterpret_cast<void*>(offset));
     assert(glGetError() == GL_NO_ERROR);
}

ComputeProgram make_compute_program(std::string name, const Shader& shader) {
     auto program = ComputeProgram(std::move(name));
     detail::build_program(program, shader);
     return program;
}

std::logic_error make_error(const Program& program) {
     auto message = std::stringstream();
     message << "Error in program('";
     message << program.getName();
     message << "'):\n";
     message << make_log(program);
     return std::logic_error(message.str());
}

std::string make_log(const Program& program) {
     auto length = GLint(0);
     glGetProgramiv(program.getId(), GL_INFO_LOG_LENGTH, &length);
     auto log = std::string(length, ' ');
     glGetProgramInfoLog(program.getId(), length, &length, &log[0]);
     return log;
}

namespace detail {

void attach(const Program& program, const Shader& shader) { glAttachShader(program.getId(), shader.getId()); }

void detach(const Program& program, const Shader& shader) { glDetachShader(program.getId(), shader.getId()); }

void link(const Program& program) {
     auto status = GLint();
     glLinkProgram(program.getId());
     glGetProgramiv(program.getId(), GL_LINK_STATUS, &status);
     if(status == GL_FALSE) throw make_error(program);
}

}//namespace detail

}//namespace happah

