#include "algernon/mesh/include/polygon.h"

namespace Algernon {

Polygon::Polygon(std::span<const Vector3f> points) : vertices_(points.begin(), points.end()) {
}

bool Polygon::IsConvex() const {
}

std::size_t Polygon::GetSize() const {
  return vertices_.size();
}

Vector3f Polygon::GetU() const {
  return glm::normalize(vertices_[1] - vertices_[0]);
}

Vector3f Polygon::GetV() const {
}

} // namespace Algernon