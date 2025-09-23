#include "algernon/mesh/include/mesh_tools.h"
#include <unordered_set>
#include <algorithm>
#include <numeric>

namespace Algernon {

std::set<Index2, Index2UnorderedComparator> GetEdgeSet(std::span<const FaceIndices> faces) {
  auto edges_view = faces                                              //
                    | std::views::transform(&FaceIndices::GetEdgeView) //
                    | std::views::join                                 //
                    | std::views::common;                              //
  return std::set<Index2, Index2UnorderedComparator>(edges_view.begin(), edges_view.end());
}

std::vector<FaceIndices> TriangulateFaces(std::span<const FaceIndices> faces) {
  auto faces_view = faces                                                      //
                    | std::views::transform(&FaceIndices::GetTriangleFaceView) //
                    | std::views::join                                         //
                    | std::views::common;                                      //
  return std::vector<FaceIndices>(faces_view.begin(), faces_view.end());
}

IndexType GetNumberVerticesInFaces(std::span<const FaceIndices> faces) {
  return std::ranges::max(faces | std::views::join) + 1;
}

IndexType GetNumberEdgesInFacesSlow(std::span<const FaceIndices> faces) {
  return GetEdgeSet(faces).size();
}

IndexType GetNumberEdgesInFacesFast(std::span<const FaceIndices> faces) {
  auto size_view = faces | std::views::transform(&FaceIndices::size);
  auto size_size = std::accumulate(size_view.begin(), size_view.end(), 0);
  return size_size / 2;
}

std::unordered_map<Index2, IndexType, Index2Hash> GetEdgeFaceMap(std::span<const FaceIndices> faces) {
  std::unordered_map<Index2, IndexType, Index2Hash> out;
  for (const auto &[face_index, face] : std::views::enumerate(faces)) {
    for (const auto &edge : face.GetEdgeView()) {
      out.emplace(edge, face_index);
    }
  }
  return out;
}

std::vector<Index2> GetUniqueEdges(std::span<const FaceIndices> faces) {
  auto edge_set = GetEdgeSet(faces);
  return std::vector<Index2>(edge_set.begin(), edge_set.end());
}

} // namespace Algernon