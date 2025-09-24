#include "algernon/geometry/include/geometry_element_walkers.h"
#include "algernon/geometry/include/geometry_elements.h"

namespace Algernon {

void VertexAdjacentVerticesWalker::Advance() {
  current_element_ = current_element_.GetNextOutgoingNeighbor();
}

VertexAdjacentVerticesWalker::return_type VertexAdjacentVerticesWalker::GetCurrent() const {
  return current_element_.GetTargetVertex();
}

void VertexAdjacentEdgesWalker::Advance() {
  current_element_ = current_element_.GetNextOutgoingNeighbor();
}

VertexAdjacentEdgesWalker::return_type VertexAdjacentEdgesWalker::GetCurrent() const {
  return current_element_.GetEdge();
}

void VertexAdjacentFacesWalker::Advance() {
  current_element_ = current_element_.GetNextOutgoingNeighbor();
}

// FACE WALKERS

Face VertexAdjacentFacesWalker::GetCurrent() const {
  return current_element_.GetFace();
}

void FaceAdjacentVerticesWalker::Advance() {
  current_element_ = current_element_.GetNextHalfedge();
}

FaceAdjacentVerticesWalker::return_type FaceAdjacentVerticesWalker::GetCurrent() const {
  return current_element_.GetSourceVertex();
}

void FaceAdjacentEdgesWalker::Advance() {
  current_element_ = current_element_.GetNextHalfedge();
}

FaceAdjacentEdgesWalker::return_type FaceAdjacentEdgesWalker::GetCurrent() const {
  return current_element_.GetEdge();
}

// EDGE WALKERS

void EdgeAdjacentFacesWalker::Advance() {
  current_element_ = current_element_.GetTwinHalfedge();
}

EdgeAdjacentFacesWalker::return_type EdgeAdjacentFacesWalker::GetCurrent() const {
  return current_element_.GetFace();
}

} // namespace Algernon