#ifndef ALGERNON_GEOMETRY_TOOLS_H
#define ALGERNON_GEOMETRY_TOOLS_H

#include <span>
#include "algernon/core/include/core_types.h"

namespace Algernon {

class FaceIndices;

struct EdgeFacet {
  Index2 edge;
  IndexType next;
  IndexType facet;
};

std::vector<EdgeFacet> GetEdgeVector(std::span<const FaceIndices> facets);
IndexType GetNumberVerticesInFaces(std::span<const FaceIndices> faces);

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_TOOLS_H