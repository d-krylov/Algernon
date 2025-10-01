#include "algernon/mesh/include/mesh_tools.h"
#include "algernon/mesh/include/face_indices.h"
#include <ranges>
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

IndexType GetNumberEdgesInFacesSlow(std::span<const FaceIndices> faces) {
  return GetEdgeSet(faces).size();
}

IndexType GetNumberEdgesInFacesFast(std::span<const FaceIndices> faces) {
  auto size_view = faces | std::views::transform(&FaceIndices::size);
  auto size_size = std::accumulate(size_view.begin(), size_view.end(), 0);
  return size_size / 2;
}

std::vector<Index2> GetUniqueEdges(std::span<const FaceIndices> faces) {
  auto edge_set = GetEdgeSet(faces);
  return std::vector<Index2>(edge_set.begin(), edge_set.end());
}

} // namespace Algernon