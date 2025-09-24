#include "algernon/geometry/include/geometry_tools.h"
#include "algernon/mesh/include/face_indices.h"
#include <ranges>
#include <algorithm>

namespace Algernon {

IndexType GetNumberVerticesInFaces(std::span<const FaceIndices> faces) {
  return std::ranges::max(faces | std::views::join) + 1;
}

std::vector<EdgeFacet> GetEdgeVector(std::span<const FaceIndices> facets) {
  std::vector<EdgeFacet> out;
  IndexType first_edge = 0;
  for (const auto &[facet_index, facet] : std::views::enumerate(facets)) {
    for (const auto &[edge_index, edge] : std::views::enumerate(facet.GetEdgeView())) {
      auto end = (edge_index == facet.size() - 1);
      out.emplace_back(edge, ++first_edge - end * facet.size(), facet_index);
    }
  }
  return out;
}

} // namespace Algernon