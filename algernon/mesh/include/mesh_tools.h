#ifndef ALGERNON_MESH_TOOLS_H
#define ALGERNON_MESH_TOOLS_H

#include "face_indices.h"
#include <set>

namespace Algernon {

IndexType GetNumberEdgesInFacesSlow(std::span<const FaceIndices> faces); // Counts the number of unique edges in faces
IndexType GetNumberEdgesInFacesFast(std::span<const FaceIndices> faces); // Counts the number of unique edges for closed surfaces
IndexType GetNumberVerticesInFaces(std::span<const FaceIndices> faces);  // Counts maximum vertex number in faces
std::vector<FaceIndices> TriangulateFaces(std::span<const FaceIndices> faces);
std::vector<Index2> GetUniqueEdges(std::span<const FaceIndices> faces); // Return vector of unique edges

std::unordered_map<Index2, IndexType, Index2Hash> GetEdgeFaceMap(std::span<const FaceIndices> faces);
std::set<Index2, Index2UnorderedComparator> GetEdgeSet(std::span<const FaceIndices> faces);

} // namespace Algernon

#endif // ALGERNON_MESH_TOOLS_H