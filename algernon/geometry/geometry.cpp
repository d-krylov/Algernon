#include "algernon/geometry/include/geometry.h"
#include "algernon/mesh/include/mesh_tools.h"

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
  return he_information_;
}

Geometry::Geometry(std::span<const Face> faces) {
  BuildExplicit(faces);
}

void Geometry::Allocate(std::span<const Face> faces) {
  he_information_.resize(geometry_statistics_.edges_ * 2);
  he_face_indices_.resize(geometry_statistics_.faces_, INVALID_INDEX);
  he_vertex_indices_.resize(geometry_statistics_.vertices_, INVALID_INDEX);
}

void Geometry::BuildImplicit(std::span<const Face> faces) {
  auto unique_edges = GetUniqueEdges(faces);
}

void Geometry::BuildExplicit(std::span<const Face> faces) {
  Allocate(faces);

  // Build halfedges without twins
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {

    IndexType he_index = 0;

    for (auto edge_index = 0; edge_index < face.size(); edge_index++) {
      auto current_face_edge = face.GetEdge(edge_index);

      he_information_[he_index].vertex_ = current_face_edge.i0; // start vertex
      he_information_[he_index].face_ = face_index;             // incident face

      he_vertex_indices_[current_face_edge.i0] = he_index;

      if (edge_index == 0) {
        he_face_indices_[face_index] = edge_index;
      } else {
      }
    }
  }
}

} // namespace Algernon