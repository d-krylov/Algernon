#ifndef ALGERNON_GEOMETRY_IPP
#define ALGERNON_GEOMETRY_IPP

#include "algernon/core/include/transform_iterator.h"

namespace Algernon {

inline auto Geometry::GetHalfedges() const {
  return BaseElements(this, &Geometry::GetHalfedge, halfedges_.size());
}

inline auto Geometry::GetFaces() const {
  return BaseElements(this, &Geometry::GetFace, face_indices_.size());
}

inline auto Geometry::GetEdges() const {
  return BaseElements(this, &Geometry::GetEdge, edge_indices_.size());
}

inline auto Geometry::GetVertices() const {
  return BaseElements(this, &Geometry::GetVertex, vertex_indices_.size());
}

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_IPP