#include "algernon/geometry/include/geometry.h"
#include "algernon/mesh/include/mesh_tools.h"
#include "algernon/mesh/include/face_indices.h"
#include <algorithm>
#include <ranges>
#include <map>
#include <print>

namespace Algernon {

struct EdgeInformation {
  Index2 edge;
  IndexType next;
  IndexType facet;
};

IndexType GetNumberVerticesInFaces(std::span<const FaceIndices> faces) {
  return std::ranges::max(faces | std::views::join) + 1;
}

auto GetEdgeInformation(std::span<const FaceIndices> facets) {
  std::vector<EdgeInformation> out;
  IndexType first_edge = 0;
  for (const auto &[facet_index, facet] : std::views::enumerate(facets)) {
    for (const auto &[facet_edge_index, edge] : std::views::enumerate(facet.GetEdgeView())) {
      auto end = (facet_edge_index == facet.size() - 1);
      out.emplace_back(edge, ++first_edge - end * facet.size(), facet_index);
    }
  }
  return out;
}

void Geometry::Allocate(std::span<const FaceIndices> faces) {
  halfedges_.reserve(geometry_statistics_.edges_ * 2);
  edges_.resize(geometry_statistics_.edges_, INVALID_INDEX);
  faces_.resize(geometry_statistics_.faces_, INVALID_INDEX);
  vertices_.resize(geometry_statistics_.vertices_, INVALID_INDEX);
}

void Geometry::BuildImplicit(std::span<const FaceIndices> facets) {
  geometry_statistics_.faces_ = facets.size();
  geometry_statistics_.vertices_ = GetNumberVerticesInFaces(facets);

  Allocate(facets);

  std::unordered_map<Index2, IndexType, Index2Hash> edge_information;

  for (const auto &[facet_index, facet] : std::views::enumerate(facets)) {
    IndexType previous_he_index = INVALID_INDEX;
    IndexType starting_he_index = INVALID_INDEX;
    for (const auto &[facet_edge_index, facet_edge] : std::views::enumerate(facet.GetEdgeView())) {
      auto previous_edge = facet_edge.GetSwapped();
      auto halfedge_index = INVALID_INDEX;
      if (edge_information.contains(previous_edge)) {
        auto previous_edge_index = edge_information[previous_edge];
        halfedge_index = GetTwinIndexImplicit(previous_edge_index);
        halfedges_[halfedge_index].face_ = facet_index;
      } else {
        halfedge_index = halfedges_.size();
        edge_information[facet_edge] = halfedge_index;
        halfedges_.emplace_back(facet_edge.i0, facet_index, INVALID_INDEX);
        halfedges_.emplace_back(facet_edge.i1, INVALID_INDEX, INVALID_INDEX);
      }
      vertices_[facet_edge.i0] = halfedge_index;
      
      if (facet_edge_index == 0) {
        faces_[facet_index] = halfedge_index;
        starting_he_index = halfedge_index;
      } else {
        halfedges_[previous_he_index].next_ = halfedge_index;
      }
      previous_he_index = halfedge_index;
    }
    halfedges_[previous_he_index].next_ = starting_he_index; 
  }
}

void Geometry::BuildExplicit(std::span<const FaceIndices> faces) {
  geometry_statistics_.faces_ = faces.size();
  geometry_statistics_.edges_ = GetNumberEdgesInFacesSlow(faces);
  geometry_statistics_.vertices_ = GetNumberVerticesInFaces(faces);

  Allocate(faces);

  auto edges_information = GetEdgeInformation(faces);

  for (const auto &[edge_index, edge_data] : std::views::enumerate(edges_information)) {
    halfedges_.emplace_back(edge_data.edge.i0, edge_data.facet, edge_data.next);
    vertices_[edge_data.edge.i0] = edge_index;
    if (faces_[edge_data.facet] == INVALID_INDEX) {
      faces_[edge_data.facet] = edge_index;
    }
  }

  he_edges_.resize(halfedges_.size(), INVALID_INDEX);
  he_twins_.resize(halfedges_.size(), INVALID_INDEX);

  std::map<Index2, IndexType, Index2UnorderedComparator> edge_he_index_map;

  IndexType edges_count = 0;

  for (const auto &[edge_index, edge_data] : std::views::enumerate(edges_information)) {
    if (edge_he_index_map.contains(edge_data.edge)) {
      auto previous_index_he = edge_he_index_map[edge_data.edge];
      auto previous_index_edge = he_edges_[previous_index_he];
      he_edges_[edge_index] = previous_index_edge;
      he_twins_[edge_index] = previous_index_he;
      edge_he_index_map[edge_data.edge] = edge_index;
    } else {
      he_edges_[edge_index] = edges_count;
      edges_[edges_count] = edge_index;
      edge_he_index_map[edge_data.edge] = edge_index;
      edges_count++;
    }
  }

  for (const auto [edge, he_index] : edge_he_index_map) {
    if (he_twins_[he_index] == INVALID_INDEX) {
      he_twins_[he_index] = he_index;
    } else {
      auto he_current = he_index;
      while (he_twins_[he_current] != INVALID_INDEX) {
        he_current = he_twins_[he_current];
      }
      he_twins_[he_current] = he_index;
    }
  }
}

void Geometry::GetBoundaryLoops() {
}

} // namespace Algernon