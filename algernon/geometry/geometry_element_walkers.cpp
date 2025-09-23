#include "algernon/geometry/include/geometry_element_walkers.h"
#include "algernon/geometry/include/geometry_elements.h"

namespace Algernon {

void VertexAdjacentVerticesWalker::Advance() {
  current_element_ = current_element_.GetNextOutgoingNeighbor();
}

Vertex VertexAdjacentVerticesWalker::GetCurrent() const {
  return current_element_.GetTargetVertex();
}

void VertexAdjacentEdgesWalker::Advance() {
  current_element_ = current_element_.GetNextOutgoingNeighbor();
}

Edge VertexAdjacentEdgesWalker::GetCurrent() const {
  return current_element_.GetEdge();
}

void VertexAdjacentFacesWalker::Advance() {
  current_element_ = current_element_.GetNextOutgoingNeighbor();
}

Face VertexAdjacentFacesWalker::GetCurrent() const {
  return current_element_.GetFace();
}

} // namespace Algernon