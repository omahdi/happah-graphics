// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>

#include "happah/graphics/Program.hpp"

namespace happah {

void activate(const Program& program, const PatchType& type) {
     glUseProgram(program.getId());
     glPatchParameteri(GL_PATCH_VERTICES, type.getSize());
}

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
     offset *= patchSize * DataType::UNSIGNED_INT.getSize();
     glDrawElements(mode, patchSize * n, DataType::UNSIGNED_INT.getId(), reinterpret_cast<void*>(offset));
     assert(glGetError() == GL_NO_ERROR);
}

void link(const Program& program) {
     auto status = GLint();
     glLinkProgram(program.getId());
     glGetProgramiv(program.getId(), GL_LINK_STATUS, &status);
     if(status == GL_FALSE) throw make_error(program);
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

void render(const Program& program, const RenderContext<GeometryType::MESH>& context, hpuint n, hpuint offset) {
     activate(context.getIndices(), context.getVertexArray());
     execute(program, context, n, offset);
}

}//namespace happah

