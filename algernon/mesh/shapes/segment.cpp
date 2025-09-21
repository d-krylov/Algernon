#include "algernon/mesh/shapes/include/segment.h"

namespace Algernon {

Segment::Segment(const Vector3f &p0, const Vector3f &p1) : p0_(p0), p1_(p1) {
}

Vector3f Segment::GetPoint(float d) const {
  return glm::mix(p0_, p1_, d);
}

} // namespace Algernon