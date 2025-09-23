#include "algernon/mesh/shapes/include/polygon.h"
#include "algernon/mesh/include/face_indices.h"
#include <numeric>

namespace Algernon {

Polygon::Polygon(std::span<const Vector3f> points) : vertices_(points.begin(), points.end()) {
}

Polygon::Polygon(std::span<const Vector3f> points, const FaceIndices &face) {
  vertices_.reserve(face.size());
  for (const auto &index : face) {
    vertices_.emplace_back(points[index]);
  }
}

bool Polygon::IsConvex() const {
}

std::size_t Polygon::size() const {
  return vertices_.size();
}

Vector3f Polygon::GetU() const {
  return glm::normalize(vertices_[1] - vertices_[0]);
}

Vector3f Polygon::GetV() const {
}

std::vector<Vector3f>::iterator Polygon::begin() {
  return vertices_.begin();
}

std::vector<Vector3f>::const_iterator Polygon::begin() const {
  return vertices_.cbegin();
}

std::vector<Vector3f>::iterator Polygon::end() {
  return vertices_.end();
}

std::vector<Vector3f>::const_iterator Polygon::end() const {
  return vertices_.cend();
}

Vector3f Polygon::GetCentroid() const {
  auto vertices_number = static_cast<float>(size());
  auto total = std::accumulate(vertices_.begin(), vertices_.end(), Vector3f(0.0f));
  return total / vertices_number;
}

} // namespace Algernon