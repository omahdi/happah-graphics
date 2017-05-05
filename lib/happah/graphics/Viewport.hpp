// Copyright 2017
//   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <happah/Happah.h>
#include <happah/math/Space.h>

namespace happah {

//TODO: move viewport to core?
class Viewport {
public:
     Viewport();

     Viewport(hpuint width, hpuint height);

     const Point3D& getEyePosition() const;

     hpuint getHeight() const;

     hpuint getOffsetX() const;

     hpuint getOffsetY() const;

     const hpmat4x4& getProjectionMatrix() const;

     const Point3D& getViewDirection() const;

     const hpmat4x4& getViewMatrix() const;

     hpuint getWidth() const;

     void rotate(hpreal x0, hpreal y0, hpreal x1, hpreal y1);

     void rotateLaterally(hpreal theta);

     void rotateLongitudinally(hpreal theta);

     void setEye(const Point3D& center, const Point3D& eyePosition, const Vector3D& up);

     void setSize(hpuint width, hpuint height);

     void translate(const Vector3D& delta);

     void translate(const Vector2D& delta);

     Point3D unproject(const Point2D& point, hpreal z) const;

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

     void updateProjectionMatrix();
     void updateViewDirection();
     void updateViewMatrix();

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

