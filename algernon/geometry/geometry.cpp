#include "algernon/geometry/include/geometry.h"

namespace Algernon {

bool Geometry::UsesImplicitTwin() const {
  return uses_implicit_twin_;
}

IndexType Geometry::GetTwinIndexImplicit(IndexType he_index) {
  return he_index ^ 1;
}

IndexType Geometry::GetEdgeIndexImplicit(IndexType he_index) {
  return he_index / 2;
}

IndexType Geometry::GetHalfedgeIndexImplicit(IndexType edge_index) {
  return edge_index * 2;
}

std::span<const Geometry::halfedge_t> Geometry::GetHalfedges() const {
  return halfedges_;
}

std::span<const IndexType> Geometry::GetFaceIndices() const {
  return face_indices_;
}

std::span<const IndexType> Geometry::GetEdgeIndices() const {
  return edge_indices_;
}

std::span<const IndexType> Geometry::GetVertexIndices() const {
  return vertex_indices_;
}

Geometry::halfedge_t Geometry::halfedge(IndexType index) const {
  return halfedges_[index];
}

IndexType Geometry::face(IndexType index) const {
  return face_indices_[index];
}

IndexType Geometry::edge(IndexType index) const {
  return edge_indices_[index];
}

IndexType Geometry::vertex(IndexType index) const {
  return vertex_indices_[index];
}

Geometry::Geometry(std::span<const FaceIndices> faces) {
  BuildExplicit(faces);
}

} // namespace Algernon