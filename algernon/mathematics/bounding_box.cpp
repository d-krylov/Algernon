#include "algernon/mathematics/include/bounding_box.h"
#include "algernon/mesh/include/polyhedron.h"

namespace Algernon {

BoundingBox::BoundingBox(const Vector3f &p0, const Vector3f &p1) : min_(glm::min(p0, p1)), max_(glm::max(p0, p1)) {
}

Polyhedron BoundingBox::GetPolyhedron() const {
}

} // namespace Algernon