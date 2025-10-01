#ifndef ALGERNON_MESH_TOOLS_H
#define ALGERNON_MESH_TOOLS_H

#include <set>
#include <span>
#include "algernon/core/include/core_types.h"

namespace Algernon {

class FaceIndices;

IndexType GetNumberEdgesInFacesFast(std::span<const FaceIndices> faces);
IndexType GetNumberEdgesInFacesSlow(std::span<const FaceIndices> faces); // Counts the number of unique edges in faces

std::vector<FaceIndices> TriangulateFaces(std::span<const FaceIndices> faces);
std::vector<Index2> GetUniqueEdges(std::span<const FaceIndices> faces); // Return vector of unique edges

std::set<Index2, Index2UnorderedComparator> GetEdgeSet(std::span<const FaceIndices> faces);

} // namespace Algernon

#endif // ALGERNON_MESH_TOOLS_H