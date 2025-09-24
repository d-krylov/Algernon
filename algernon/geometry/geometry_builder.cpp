#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_tools.h"
#include "algernon/mesh/include/mesh_tools.h"
#include "algernon/mesh/include/face_indices.h"
#include <ranges>
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

  auto edge_vector = GetEdgeVector(faces);

  for (const auto &[edge_index, edge_data] : std::views::enumerate(edge_vector)) {
    halfedges_.emplace_back(edge_data.edge.i0, edge_data.facet, edge_data.next);
    vertex_indices_[edge_data.edge.i0] = edge_index;
    if (face_indices_[edge_data.facet] == INVALID_INDEX) {
      face_indices_[edge_data.facet] = edge_index;
    }
  }

  std::map<Index2, IndexType, Index2UnorderedComparator> edge_he_index_map;

  IndexType edges_count = 0;

  for (const auto &[edge_index, edge_data] : std::views::enumerate(edge_vector)) {
    if (edge_he_index_map.contains(edge_data.edge)) {
      auto previous_index_he = edge_he_index_map[edge_data.edge];
      auto previous_index_edge = halfedges_[previous_index_he].edge_;
      halfedges_[edge_index].edge_ = previous_index_edge;
      halfedges_[edge_index].twin_ = previous_index_he;
      edge_he_index_map[edge_data.edge] = edge_index;
    } else {
      halfedges_[edge_index].edge_ = edges_count;
      edge_indices_[edges_count] = edge_index;
      edge_he_index_map[edge_data.edge] = edge_index;
      edges_count++;
    }
  }

  for (const auto [edge, he_index] : edge_he_index_map) {
    if (halfedges_[he_index].twin_ == INVALID_INDEX) {
      halfedges_[he_index].twin_ = he_index;
    } else {
      auto he_current = he_index;
      while (halfedges_[he_current].twin_ != INVALID_INDEX) {
        he_current = halfedges_[he_current].twin_;
      }
      halfedges_[he_current].twin_ = he_index;
    }
  }
}

} // namespace Algernon