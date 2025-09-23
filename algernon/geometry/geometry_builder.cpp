#include "algernon/geometry/include/geometry.h"
#include "algernon/mesh/include/mesh_tools.h"
#include <map>
#include <print>

namespace Algernon {

void Geometry::Allocate(std::span<const FaceIndices> faces) {
  halfedges_.reserve(geometry_statistics_.edges_ * 2);
  he_edges_.reserve(geometry_statistics_.edges_ * 2);
  edge_indices_.resize(geometry_statistics_.edges_, INVALID_INDEX);
  face_indices_.resize(geometry_statistics_.faces_, INVALID_INDEX);
  vertex_indices_.resize(geometry_statistics_.vertices_, INVALID_INDEX);
}

void Geometry::BuildImplicit(std::span<const FaceIndices> faces) {
  auto unique_edges = GetUniqueEdges(faces);
}

void Geometry::BuildExplicit(std::span<const FaceIndices> faces) {
  geometry_statistics_.faces_ = faces.size();
  geometry_statistics_.edges_ = GetNumberEdgesInFacesSlow(faces);
  geometry_statistics_.vertices_ = GetNumberVerticesInFaces(faces);

  Allocate(faces);

  // Build halfedges without twins
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {
    IndexType first_he_index = INVALID_INDEX;
    IndexType previous_he_index = INVALID_INDEX;
    for (auto edge_index = 0; edge_index < face.size(); edge_index++) {
      auto current_face_edge = face.GetEdge(edge_index);
      auto he_index = halfedges_.size();
      auto &new_halfedge = halfedges_.emplace_back();

      new_halfedge.vertex_ = current_face_edge.i0; // start vertex
      new_halfedge.face_ = face_index;             // incident face

      vertex_indices_[current_face_edge.i0] = he_index;

      if (edge_index == 0) {
        face_indices_[face_index] = he_index;
        first_he_index = he_index;
      } else {
        halfedges_[previous_he_index].next_ = he_index;
      }

      previous_he_index = he_index;
    }

    halfedges_[previous_he_index].next_ = first_he_index;
  }

  std::map<Index2, IndexType, Index2UnorderedComparator> edge_history;

  IndexType he_index = 0;
  IndexType edges_count = 0;
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {
    for (auto edge_index = 0; edge_index < face.size(); edge_index++) {
      auto current_face_edge = face.GetEdge(edge_index);
      if (edge_history.contains(current_face_edge) == false) {
        halfedges_[he_index].edge_ = edges_count;
        edge_indices_[edges_count] = he_index;
        edge_history[current_face_edge] = he_index;
        edges_count++;
      } else {
        auto he_previous = edge_history[current_face_edge];
        auto ie = halfedges_[he_previous].edge_;
        halfedges_[he_index].edge_ = ie;
        halfedges_[he_index].twin_ = he_previous;
        edge_history[current_face_edge] = he_index;
      }
      he_index++;
    }
  }

  for (const auto [edge, edge_index] : edge_history) {

    if (halfedges_[edge_index].twin_ == INVALID_INDEX) {
      halfedges_[edge_index].twin_ = edge_index;
      continue;
    }

    auto he_current = edge_index;

    while (halfedges_[he_current].twin_ != INVALID_INDEX) {
      he_current = halfedges_[he_current].twin_;
    }
    halfedges_[he_current].twin_ = edge_index;
  }
}

} // namespace Algernon