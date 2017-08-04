// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#define GLM_FORCE_RADIANS

#include "happah/graphics/Viewport.hpp"

namespace happah {

//NOTE: Input coordinates must be relative to an origin in the bottom left with the positive y-axis pointing up and the positive x-axis pointing to the right.
void Viewport::rotate(hpreal x0, hpreal y0, hpreal x1, hpreal y1) {
     auto t = glm::length(m_eyePosition - m_center);
     auto c = Point2D(m_width / 2.0f, m_height / 2.0f);
     auto r = glm::min(c.x, c.y);// imagine sphere centered at center of screen
     auto r2 = r * r;
     auto q0 = Vector2D(x0, y0) - c;
     auto q1 = Vector2D(x1, y1) - c;
     auto d0 = glm::length2(q0);
     auto d1 = glm::length2(q1);
     auto z0 = glm::sqrt((d0 < r2 / 2.0f) ? r2 - d0 : r2 * r2 / (4.0f * d0));
     auto z1 = glm::sqrt((d1 < r2 / 2.0f) ? r2 - d1 : r2 * r2 / (4.0f * d1));
     auto p0 = glm::normalize(Vector3D(q0, z0));
     auto p1 = glm::normalize(Vector3D(q1, z1));
     auto axis = glm::cross(p1, p0);
     auto angle = glm::atan(glm::clamp(glm::length(axis), -1.0f, 1.0f), glm::clamp(glm::dot(p0, p1), -1.0f, 1.0f));// angle of rotation about center of screen
     angle = -glm::atan((t - r * glm::cos(angle / 2.0f)) / (r * glm::sin(angle / 2.0f)));// angle of rotation about center of scene
     auto q = glm::angleAxis(angle, axis);
     auto R = glm::inverse(m_viewMatrix) * glm::toMat4(glm::normalize(q)) * m_viewMatrix;
     m_viewDirection = glm::normalize(Vector3D(R * Vector4D(m_viewDirection, 0.0f)));
     m_eyePosition = m_center - t * m_viewDirection;
     m_up = glm::normalize(Vector3D(R * Vector4D(m_up, 0.0f)));
     updateViewMatrix();
}

void Viewport::rotateLaterally(hpreal theta) {
     auto forward = m_center - m_eyePosition;
     auto distance = glm::length(forward);
     auto right = distance * glm::normalize(glm::cross(m_up, forward));
     m_eyePosition = m_center - std::cos(theta) * forward + std::sin(theta) * right;
     updateViewDirection();
     updateViewMatrix();
}

void Viewport::rotateLongitudinally(hpreal theta) {
     auto forward = m_center - m_eyePosition;
     auto distance = glm::length(forward);
     auto right = glm::cross(m_up, forward);
     auto up = distance * m_up;
     auto delta = std::sin(theta) * up - std::cos(theta) * forward;
     m_eyePosition = m_center + delta;
     m_up = glm::normalize(glm::cross(-delta, right));
     updateViewDirection();
     updateViewMatrix();
}

void Viewport::setEye(const Point3D& center, const Point3D& eyePosition, const Vector3D& up) {
     m_center = center;
     m_eyePosition = eyePosition;
     m_up = glm::normalize(up);
     updateViewDirection();
     updateViewMatrix();
}

void Viewport::setSize(hpuint width, hpuint height) {
     m_width = width;
     m_height = height;
     updateProjectionMatrix();
}

void Viewport::translate(const Vector3D& delta) {
     m_center += delta;
     m_eyePosition += delta;
     updateViewDirection();
     updateViewMatrix();
}

void Viewport::translate(const Vector2D& delta) {
     auto forward = m_center - m_eyePosition;
     auto distance = glm::length(forward);
     auto right = glm::normalize(glm::cross(m_up, forward));
     translate(distance * (delta.x * right + delta.y * m_up));
}

void Viewport::zoom(hpreal delta) {
     auto forward = m_center - m_eyePosition;
     m_eyePosition += delta * forward;
     //TODO: make sure eye is never center
     updateViewDirection();
     updateViewMatrix();
}

}//namespace happah

