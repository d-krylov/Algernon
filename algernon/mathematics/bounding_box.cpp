#include "algernon/mathematics/include/bounding_box.h"
#include "algernon/mesh/shapes/include/polyhedron.h"

namespace Algernon {

BoundingBox::BoundingBox(const Vector3f &p0, const Vector3f &p1) : min_(glm::min(p0, p1)), max_(glm::max(p0, p1)) {
}

Polyhedron BoundingBox::GetPolyhedron() const {
  std::vector<Vector3f> vertices{
    {min_.x, min_.y, max_.z}, //
    {max_.x, min_.y, max_.z}, //
    {max_.x, max_.y, max_.z}, //
    {min_.x, max_.y, max_.z}, //
    {min_.x, min_.y, min_.z}, //
    {max_.x, min_.y, min_.z}, //
    {max_.x, max_.y, min_.z}, //
    {min_.x, max_.y, min_.z}, //
  };

  std::vector<Face> faces{
    {0, 1, 2, 3}, // FRONT
    {1, 5, 6, 2}, // RIGHT
    {5, 4, 7, 6}, // BACK
    {4, 0, 3, 7}, // LEFT
    {3, 2, 6, 7}, // TOP
    {4, 5, 1, 0}  // BOTTOM
  };

  return Polyhedron(vertices, faces);
}

} // namespace Algernon