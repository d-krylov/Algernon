#include "algernon/mesh/include/plane.h"

namespace Algernon {

Plane::Plane(const Vector3f normal, float offset) : normal_(normal), offset_(offset) {
}

Plane::Plane(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2) {
  auto v0 = p1 - p0;
  auto v1 = p2 - p0;
  normal_ = glm::cross(v0, v1);
  normal_ = glm::normalize(normal_);
  offset_ = glm::dot(normal_, p0);
}

const Vector3f &Plane::GetNormal() const {
  return normal_;
}

float Plane::GetOffset() const {
  return offset_;
}

float Plane::GetSignedDistance(const Vector3f &point) const {
  return glm::dot(normal_, point) - offset_;
}

} // namespace Algernon