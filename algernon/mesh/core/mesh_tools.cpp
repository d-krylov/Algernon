#include "algernon/mesh/include/mesh_tools.h"
#include <unordered_set>
#include <algorithm>
#include <numeric>

namespace Algernon {

IndexType GetNumberVerticesInFacesSlow(std::span<const Face> faces) {
  auto vertices_view = faces | std::views::join | std::views::common;
  std::unordered_set<IndexType> vertices_set(vertices_view.begin(), vertices_view.end());
  return vertices_set.size();
}

IndexType GetNumberVerticesInFacesFast(std::span<const Face> faces) {
  return std::ranges::max(faces | std::views::join) + 1;
}

std::set<Index2, Index2UnorderedComparator> GetEdgeSet(std::span<const Face> faces) {
  auto edges_view = faces | std::views::transform(&Face::GetEdgeView) | std::views::join | std::views::common;
  return std::set<Index2, Index2UnorderedComparator>(edges_view.begin(), edges_view.end());
}

IndexType GetNumberEdgesInFacesSlow(std::span<const Face> faces) {
  auto edges_set = GetEdgeSet(faces);
  return edges_set.size();
}

IndexType GetNumberEdgesInFacesFast(std::span<const Face> faces) {
  auto size_view = faces | std::views::transform(&Face::size);
  auto size_size = std::accumulate(size_view.begin(), size_view.end(), 0);
  return size_size / 2;
}

std::vector<Face> TriangulateFaces(std::span<const Face> faces) {
  auto faces_view = faces | std::views::transform(&Face::GetTriangleFaceView) | std::views::join | std::views::common;
  return std::vector<Face>(faces_view.begin(), faces_view.end());
}

std::unordered_map<Index2, IndexType, Index2Hash> GetEdgeFaceMap(std::span<const Face> faces) {
  std::unordered_map<Index2, IndexType, Index2Hash> out;
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {
    for (const auto &edge : face.GetEdgeView()) {
      out.emplace(edge, face_index);
    }
  }
  return out;
}

std::vector<Index2> GetUniqueEdges(std::span<const Face> faces) {
  auto edge_set = GetEdgeSet(faces);
  return std::vector<Index2>(edge_set.begin(), edge_set.end());
}

} // namespace Algernon