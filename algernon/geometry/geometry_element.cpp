#include "algernon/geometry/include/geometry_element.h"
#include "algernon/geometry/include/geometry.h"

namespace Algernon {

IndexType GeometryElement::GetIndex() const {
  return index_;
}

GeometryElement::GeometryElement(const Geometry *geometry, IndexType index) : geometry_(geometry), index_(index) {
}

GeometryVertex::GeometryVertex(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

GeometryEdge::GeometryEdge(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

GeometryFace::GeometryFace(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

} // namespace Algernon