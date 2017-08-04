// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <happah/Happah.hpp>
#include <happah/math/Space.hpp>

namespace happah {

//TODO: move viewport to core?
class Viewport {
public:
     Viewport() : Viewport(0, 0) {}

     Viewport(hpuint width, hpuint height)
     : m_center(0.0), m_eyePosition(0.0,0.0,1.0), m_farZ(1000.0), m_fieldOfViewAngleY(45.0), m_height(height), m_nearZ(0.1), m_offsetX(0), m_offsetY(0), m_up(0.0,1.0,0.0), m_viewDirection(glm::normalize(m_center-m_eyePosition)), m_viewMatrix(glm::lookAt(m_eyePosition, m_center, m_up)), m_width(width) { updateProjectionMatrix(); }
     const Point3D& getEyePosition() const;

     hpuint getHeight() const { return m_height; }

     hpuint getOffsetX() const { return m_offsetX; }

     hpuint getOffsetY() const { return m_offsetY; }

     const hpmat4x4& getProjectionMatrix() const { return m_projectionMatrix; }

     const Point3D& getViewDirection() const { return m_viewDirection; }

     const hpmat4x4& getViewMatrix() const { return m_viewMatrix; }

     hpuint getWidth() const { return m_width; }

     void rotate(hpreal x0, hpreal y0, hpreal x1, hpreal y1);

     void rotateLaterally(hpreal theta);

     void rotateLongitudinally(hpreal theta);

     void setEye(const Point3D& center, const Point3D& eyePosition, const Vector3D& up);

     void setSize(hpuint width, hpuint height);

     void translate(const Vector3D& delta);

     void translate(const Vector2D& delta);

     Point3D unproject(const Point2D& point, hpreal z) const { return glm::unProject(Point3D(point.x, point.y, z), m_viewMatrix, m_projectionMatrix, glm::vec4(m_offsetX, m_offsetY, m_width, m_height)); }

     void zoom(hpreal delta);

private:
     Point3D m_center;
     Point3D m_eyePosition;
     hpreal m_farZ;
     hpreal m_fieldOfViewAngleY;
     hpuint m_height;
     hpreal m_nearZ;
     hpuint m_offsetX;
     hpuint m_offsetY;
     hpmat4x4 m_projectionMatrix;
     Vector3D m_up;
     Vector3D m_viewDirection;
     hpmat4x4 m_viewMatrix;
     hpuint m_width;

     void updateProjectionMatrix() { m_projectionMatrix = glm::perspective(m_fieldOfViewAngleY, (hpreal) m_width / (hpreal) m_height, m_nearZ, m_farZ); }

     void updateViewDirection() { m_viewDirection = glm::normalize(m_center - m_eyePosition); }

     void updateViewMatrix() { m_viewMatrix = glm::lookAt(m_eyePosition, m_center, m_up); }

};

template<class Vertex>
void look_at(Viewport& viewport, const std::vector<Vertex>& vertices) {
     auto center = Point3D(0.0);
     auto min = Point3D(vertices[0].position);
     auto max = Point3D(vertices[0].position);
     for(auto& vertex : vertices) {
          center += vertex.position;
          min = glm::min(min, vertex.position);
          max = glm::max(max, vertex.position);
     }
     center /= vertices.size();
     auto eyePosition = center;
     eyePosition.z -= 2 * glm::length(max - min);
     viewport.setEye(center, eyePosition, Vector3D(0, 1, 0));
}

}//namespace happah

