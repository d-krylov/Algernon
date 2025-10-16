#ifndef ALGERNON_GEOMETRY_IPP
#define ALGERNON_GEOMETRY_IPP

#include "algernon/core/include/transform_iterator.h"

namespace Algernon {

inline auto Geometry::GetHalfedges() const {
  return BaseElements(this, &Geometry::GetHalfedge, GetHalfedgesSize());
}

inline auto Geometry::GetFaces() const {
  return BaseElements(this, &Geometry::GetFace, GetFacesSize());
}

inline auto Geometry::GetEdges() const {
  return BaseElements(this, &Geometry::GetEdge, edges_.size());
}

inline auto Geometry::GetVertices() const {
  return BaseElements(this, &Geometry::GetVertex, GetVerticesSize());
}

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_IPP