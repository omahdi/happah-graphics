// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "happah/graphics/Buffer.hpp"

namespace happah {

Buffer::Buffer(hpuint n, const DataType& type, GLsizei stride, GLenum usage)
     : m_size(n), m_stride(stride), m_type(std::move(type)) {
     glCreateBuffers(1, &m_id);
     glNamedBufferData(m_id, m_size * m_type.getSize(), NULL, usage);
}

Buffer make_buffer(const Indices& indices, GLenum usage) {
     auto buffer = make_buffer(indices.size(), DataType::UNSIGNED_INT, 0, usage);
     write(buffer, indices);
     return buffer;
}

Buffer make_buffer(const std::vector<glm::highp_vec2>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::highp_vec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 0.f, 1.f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::lowp_vec2>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::lowp_vec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 0.f, 1.f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::mediump_vec2>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::mediump_vec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 0.f, 1.f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::highp_dvec2>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::highp_dvec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 0.f, 1.f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::highp_vec3>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::highp_vec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 1.0f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::lowp_vec3>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::lowp_vec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 1.0f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::mediump_vec3>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::mediump_vec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 1.0f);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::highp_dvec3>& vecs, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<glm::highp_dvec4>();
     temp.reserve(vecs.size());
     for(auto& vec : vecs) temp.emplace_back(vec, 1.0);
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<glm::highp_vec4>& vecs, GLenum usage) {
     auto buffer = make_buffer(vecs.size() << 2, DataType::FLOAT, 4, usage);
     write(buffer, vecs);
     return buffer;
}

Buffer make_buffer(const std::vector<glm::lowp_vec4>& vecs, GLenum usage) {
     auto buffer = make_buffer(vecs.size() << 2, DataType::FLOAT, 4, usage);
     write(buffer, vecs);
     return buffer;
}

Buffer make_buffer(const std::vector<glm::mediump_vec4>& vecs, GLenum usage) {
     auto buffer = make_buffer(vecs.size() << 2, DataType::FLOAT, 4, usage);
     write(buffer, vecs);
     return buffer;
}

Buffer make_buffer(const std::vector<glm::highp_dvec4>& vecs, GLenum usage) {
     auto buffer = make_buffer(vecs.size() << 2, DataType::DOUBLE, 4, usage);
     write(buffer, vecs);
     return buffer;
}

Buffer make_buffer(const std::vector<VertexP2>& vertices, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<Point4D>();
     temp.reserve(vertices.size());
     for(auto& vertex : vertices) temp.emplace_back(vertex.position, hpreal(0.0), hpreal(1.0));
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<VertexP3>& vertices, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<Point4D>();
     temp.reserve(vertices.size());
     for(auto& vertex : vertices) temp.emplace_back(vertex.position, hpreal(1.0));
     return make_buffer(temp, usage);
}

Buffer make_buffer(const std::vector<VertexP4>& vertices, GLenum usage) {
     //TODO: write directly into buffer instead of temporary?
     auto temp = std::vector<Point4D>();
     temp.reserve(vertices.size());
     for(auto& vertex : vertices) temp.emplace_back(vertex.position);
     return make_buffer(temp, usage);
}

}//namespace happah

