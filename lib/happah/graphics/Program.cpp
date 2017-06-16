// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>

#include "happah/graphics/Program.hpp"

namespace happah {

PatchType::PatchType(GLenum id, GLuint size)
     : m_id(id), m_size(size) {}

GLenum PatchType::getId() const { return m_id; }

GLuint PatchType::getSize() const { return m_size; }

const PatchType PatchTypes::LOOP_BOX_SPLINE = { GL_PATCHES, 12 };
const PatchType PatchTypes::QUINTIC = { GL_PATCHES, 21 };
const PatchType PatchTypes::TRIANGLE = { GL_TRIANGLES, 3 };

RenderContext<GeometryType::ARRAY>::RenderContext(const VertexArray& array, const PatchType& type)
     : m_array(array), m_type(type) {}

const PatchType& RenderContext<GeometryType::ARRAY>::getType() const { return m_type; }

const VertexArray& RenderContext<GeometryType::ARRAY>::getVertexArray() const { return m_array; }

RenderContext<GeometryType::MESH>::RenderContext(const VertexArray& array, const Buffer& indices, const PatchType& type)
     : m_array(array), m_indices(indices), m_type(type) {}

const Buffer& RenderContext<GeometryType::MESH>::getIndices() const { return m_indices; }

const PatchType& RenderContext<GeometryType::MESH>::getType() const { return m_type; }

const VertexArray& RenderContext<GeometryType::MESH>::getVertexArray() const { return m_array; }

RenderContext<GeometryType::ARRAY> make_render_context(const VertexArray& array, const PatchType& type) { return { array, type }; }

RenderContext<GeometryType::MESH> make_render_context(const VertexArray& array, const Buffer& indices, const PatchType& type) { return { array, indices, type }; }

Program::Program(std::string name)
     : m_id(glCreateProgram()), m_name(std::move(name)) {}

Program::~Program() { glDeleteProgram(m_id); }

GLuint Program::getId() const { return m_id; }

const std::string& Program::getName() const { return m_name; }

void activate(const Program& program) { glUseProgram(program.getId()); }

void activate(const Program& program, hpuint patchSize) {
     glUseProgram(program.getId());
     glPatchParameteri(GL_PATCH_VERTICES, patchSize);
}

void attach(const Program& program, const Shader& shader) { glAttachShader(program.getId(), shader.getId()); }

void detach(const Program& program, const Shader& shader) { glDetachShader(program.getId(), shader.getId()); }

void execute(const Program& program, hpuint nx, hpuint ny, hpuint nz) {
     glDispatchCompute(nx, ny, nz);
     assert(glGetError() == GL_NO_ERROR);
}

void execute(const Program& program, const RenderContext<GeometryType::ARRAY>& context, hpuint n, hpuint offset) {
     auto mode = context.getType().getId();
     auto patchSize = context.getType().getSize();
     glDrawArrays(mode, patchSize * offset, patchSize * n);
     assert(glGetError() == GL_NO_ERROR);
}

void execute(const Program& program, const RenderContext<GeometryType::MESH>& context, hpuint n, hpuint offset) {
     auto mode = context.getType().getId();
     auto patchSize = context.getType().getSize();
     offset *= patchSize * Types::UNSIGNED_INT.getSize();
     glDrawElements(mode, patchSize * n, Types::UNSIGNED_INT.getId(), reinterpret_cast<void*>(offset));
     assert(glGetError() == GL_NO_ERROR);
}

void link(const Program& program) {
     auto status = GLint();
     glLinkProgram(program.getId());
     glGetProgramiv(program.getId(), GL_LINK_STATUS, &status);
     if(status == GL_FALSE) throw make_error(program);
}

Program make_program(std::string name) { return { std::move(name) }; }

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

void render(const Program& program, const RenderContext<GeometryType::ARRAY>& context, hpuint n, hpuint offset) { execute(program, context, n, offset); }

void render(const Program& program, const RenderContext<GeometryType::MESH>& context, hpuint n, hpuint offset) {
     activate(context.getVertexArray(), context.getIndices());
     execute(program, context, n, offset);
}

void render(const Program& program, const RenderContext<GeometryType::MESH>& context) { render(program, context, context.getIndices().getSize() / context.getType().getSize()); }

}//namespace happah

