#include "algernon/geometry/include/geometry.h"
#include "algernon/mesh/include/mesh_tools.h"
#include <map>
#include <print>

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

std::span<const IndexType> Geometry::GetFaceIndices() const {
  return he_face_indices_;
}

std::span<const IndexType> Geometry::GetEdgeIndices() const {
  return he_edge_indices_;
}

std::span<const IndexType> Geometry::GetVertexIndices() const {
  return he_vertex_indices_;
}

Geometry::Geometry(std::span<const Face> faces) {
  BuildExplicit(faces);
}

void Geometry::Allocate(std::span<const Face> faces) {
  he_information_.reserve(geometry_statistics_.edges_ * 2);
  he_edge_indices_.resize(geometry_statistics_.edges_, INVALID_INDEX);
  he_face_indices_.resize(geometry_statistics_.faces_, INVALID_INDEX);
  he_vertex_indices_.resize(geometry_statistics_.vertices_, INVALID_INDEX);
}

void Geometry::BuildImplicit(std::span<const Face> faces) {
  auto unique_edges = GetUniqueEdges(faces);
}

void Geometry::BuildExplicit(std::span<const Face> faces) {
  geometry_statistics_.faces_ = faces.size();
  geometry_statistics_.edges_ = GetNumberEdgesInFacesSlow(faces);
  geometry_statistics_.vertices_ = GetNumberVerticesInFacesFast(faces);

  Allocate(faces);

  // Build halfedges without twins
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {
    IndexType first_he_index = INVALID_INDEX;
    IndexType previous_he_index = INVALID_INDEX;
    for (auto edge_index = 0; edge_index < face.size(); edge_index++) {
      auto current_face_edge = face.GetEdge(edge_index);
      auto he_index = he_information_.size();
      auto &new_halfedge = he_information_.emplace_back();

      new_halfedge.vertex_ = current_face_edge.i0; // start vertex
      new_halfedge.face_ = face_index;             // incident face

      he_vertex_indices_[current_face_edge.i0] = he_index;

      if (edge_index == 0) {
        he_face_indices_[face_index] = he_index;
        first_he_index = he_index;
      } else {
        he_information_[previous_he_index].next_ = he_index;
      }

      previous_he_index = he_index;
    }

    he_information_[previous_he_index].next_ = first_he_index;
  }

  std::map<Index2, IndexType, Index2UnorderedComparator> edge_history;

  IndexType he_index = 0;
  IndexType edges_count = 0;
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {
    for (auto edge_index = 0; edge_index < face.size(); edge_index++) {
      auto current_face_edge = face.GetEdge(edge_index);
      if (edge_history.contains(current_face_edge) == false) {
        he_information_[he_index].edge_ = edges_count;
        he_edge_indices_[edges_count] = he_index;
        edge_history[current_face_edge] = he_index;
        edges_count++;
      } else {
        auto he_previous = edge_history[current_face_edge];
        auto ie = he_information_[he_previous].edge_;
        he_information_[he_index].edge_ = ie;
        he_information_[he_index].twin_ = he_previous;
        edge_history[current_face_edge] = he_index;
      }
      he_index++;
    }
  }

  for (const auto [edge, edge_index] : edge_history) {

    if (he_information_[edge_index].twin_ == INVALID_INDEX) {
      he_information_[edge_index].twin_ = edge_index;
      continue;
    }

    auto he_current = edge_index;

    while (he_information_[he_current].twin_ != INVALID_INDEX) {
      he_current = he_information_[he_current].twin_;
    }
    he_information_[he_current].twin_ = edge_index;
  }
}

} // namespace Algernon