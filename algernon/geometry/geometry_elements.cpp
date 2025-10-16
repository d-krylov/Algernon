#include "algernon/geometry/include/geometry_elements.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include "algernon/geometry/include/geometry.h"

namespace Algernon {

// GEOMETRY ELEMENT

IndexType GeometryElement::GetIndex() const {
  return index_;
}

GeometryElement::operator IndexType() const {
  return index_;
}

const Geometry *GeometryElement::GetGeometry() const {
  return geometry_;
}

std::strong_ordering GeometryElement::operator<=>(const GeometryElement &other) const {
  return index_ <=> other.index_;
}

bool GeometryElement::IsValid() const {
  return GetIndex() != INVALID_INDEX;
}

GeometryElement::GeometryElement(const Geometry *geometry, IndexType index) : geometry_(geometry), index_(index) {
}

// VERTEX
Vertex::Vertex(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Halfedge Vertex::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->get_vertex(GetIndex()));
}

bool Vertex::IsValid() const {
  return geometry_->IsVertexValid(GetIndex());
}

bool Vertex::IsBoundary() const {
}

std::size_t Vertex::GetEdgeDegree() const {
  std::size_t ret = 0;
  for (const auto &edge : GetAdjacentEdges()) {
    ret++;
  }
  return ret;
}

std::size_t Vertex::GetFaceDegree() const {
  std::size_t ret = 0;
  for (const auto &face : GetAdjacentFaces()) {
    ret++;
  }
  return ret;
}

GeometryIterator<VertexAdjacentVerticesWalker> Vertex::GetAdjacentVertices() const {
  return GeometryIterator<VertexAdjacentVerticesWalker>(GetHalfedge());
}

GeometryIterator<VertexAdjacentEdgesWalker> Vertex::GetAdjacentEdges() const {
  return GeometryIterator<VertexAdjacentEdgesWalker>(GetHalfedge());
}

GeometryIterator<VertexAdjacentFacesWalker> Vertex::GetAdjacentFaces() const {
  return GeometryIterator<VertexAdjacentFacesWalker>(GetHalfedge());
}

// EDGE
Edge::Edge(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Vertex Edge::GetSourceVertex() const {
  return GetHalfedge().GetSourceVertex();
}

Vertex Edge::GetTargetVertex() const {
  return GetHalfedge().GetTargetVertex();
}

bool Edge::IsBoundary() const {
}

Halfedge Edge::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->get_edge(GetIndex()));
}

GeometryIterator<EdgeAdjacentFacesWalker> Edge::GetAdjacentFaces() const {
  return GeometryIterator<EdgeAdjacentFacesWalker>(GetHalfedge());
}

// FACE
Face::Face(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

std::size_t Face::GetDegree() const {
  std::size_t ret = 0;
  for (const auto &vertex : GetAdjacentVertices()) {
    ret++;
  }
  return ret;
}

Halfedge Face::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->get_face(GetIndex()));
}

bool Face::IsBoundary() const {
}

bool Face::IsValid() const {
  return geometry_->IsFaceValid(GetIndex());
}

GeometryIterator<FaceAdjacentVerticesWalker> Face::GetAdjacentVertices() const {
  return GeometryIterator<FaceAdjacentVerticesWalker>(GetHalfedge());
}

GeometryIterator<FaceAdjacentEdgesWalker> Face::GetAdjacentEdges() const {
  return GeometryIterator<FaceAdjacentEdgesWalker>(GetHalfedge());
}

GeometryIterator<FaceAdjacentHalfedgesWalker> Face::GetAdjacentHalfedges() const {
  return GeometryIterator<FaceAdjacentHalfedgesWalker>(GetHalfedge());
}

// HALFEDGE
Halfedge::Halfedge(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Halfedge Halfedge::GetNextHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->get_halfedge(index_).next_);
}

Halfedge Halfedge::GetTwinHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->get_twin(GetIndex()));
}

Halfedge Halfedge::GetPreviousHalfedge() const {
  auto current_halfedge = *this;
  auto next_halfedge = GetNextHalfedge();
  while (next_halfedge != *this) {
    current_halfedge = next_halfedge;
    next_halfedge = current_halfedge.GetNextHalfedge();
  }
  return current_halfedge;
}

Halfedge Halfedge::GetPreviousOutgoingNeighbor() const {
  auto current_halfedge = *this;
  while (current_halfedge.GetNextOutgoingNeighbor() != *this) {
    current_halfedge = current_halfedge.GetNextOutgoingNeighbor();
  }
  return current_halfedge.GetTwinHalfedge();
}

Vertex Halfedge::GetSourceVertex() const {
  return Vertex(GetGeometry(), GetGeometry()->get_halfedge(index_).vertex_);
}

Vertex Halfedge::GetTargetVertex() const {
  return GetNextHalfedge().GetSourceVertex();
}

Halfedge Halfedge::GetNextOutgoingNeighbor() const {
  return GetTwinHalfedge().GetNextHalfedge();
}

Halfedge Halfedge::GetNextIncomingNeighbor() const {
  return GetNextHalfedge().GetTwinHalfedge();
}

Edge Halfedge::GetEdge() const {
  return Edge(GetGeometry(), GetGeometry()->get_edge(GetIndex()));
}

Face Halfedge::GetFace() const {
  return Face(GetGeometry(), GetGeometry()->get_halfedge(GetIndex()).face_);
}

bool Halfedge::IsBoundary() const {
}

} // namespace Algernon