#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include "algernon/mesh/include/face_indices.h"

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

Halfedge Geometry::GetHalfedge(IndexType index) const {
  return Halfedge(this, index);
}

Vertex Geometry::GetVertex(IndexType index) const {
  return Vertex(this, index);
}

Face Geometry::GetFace(IndexType index) const {
  return Face(this, index);
}

Edge Geometry::GetEdge(IndexType index) const {
  return Edge(this, index);
}

Geometry::Geometry(std::span<const FaceIndices> faces) {
  BuildExplicit(faces);
}

std::vector<FaceIndices> Geometry::GetFaceIndices() const {
  std::vector<FaceIndices> out;
  for (const auto &face : GetFaces()) {
    std::vector<IndexType> vertices;
    for (const auto &vertex : face.GetAdjacentVerices()) {
      vertices.emplace_back(vertex.GetIndex());
    }
    out.emplace_back(vertices);
  }
  return out;
}

} // namespace Algernon