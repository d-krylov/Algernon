#ifndef ALGERNON_MESH_TOOLS_H
#define ALGERNON_MESH_TOOLS_H

#include "face.h"
#include <set>

namespace Algernon {

IndexType GetNumberEdgesInFacesSlow(std::span<const Face> faces);    // Counts the number of unique edges in faces
IndexType GetNumberEdgesInFacesFast(std::span<const Face> faces);    // Counts the number of unique edges for closed surfaces
IndexType GetNumberVerticesInFacesSlow(std::span<const Face> faces); // Counts the number of unique vertices in faces
IndexType GetNumberVerticesInFacesFast(std::span<const Face> faces); // Counts maximum vertex number in faces
std::vector<Face> TriangulateFaces(std::span<const Face> faces);
std::vector<Index2> GetUniqueEdges(std::span<const Face> faces); // Return vector of unique edges

std::unordered_map<Index2, IndexType, Index2Hash> GetEdgeFaceMap(std::span<const Face> faces);
std::set<Index2, Index2UnorderedComparator> GetEdgeSet(std::span<const Face> faces);

} // namespace Algernon

#endif // ALGERNON_MESH_TOOLS_H