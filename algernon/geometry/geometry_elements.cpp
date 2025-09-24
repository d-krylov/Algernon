#include "algernon/geometry/include/geometry_elements.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include "algernon/geometry/include/geometry.h"

namespace Algernon {

IndexType GeometryElement::GetIndex() const {
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
  return Halfedge(GetGeometry(), GetGeometry()->vertex(GetIndex()));
}

std::size_t Vertex::GetDegree() const {
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

Halfedge Edge::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->edge(GetIndex()));
}

GeometryIterator<EdgeAdjacentFacesWalker> Edge::GetAdjacentFaces() const {
  return GeometryIterator<EdgeAdjacentFacesWalker>(GetHalfedge());
}

// FACE
Face::Face(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

std::size_t Face::GetDegree() const {
  std::size_t ret = 0;
  for (const auto &vertex : GetAdjacentVerices()) {
    ret++;
  }
  return ret;
}

Halfedge Face::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->face(GetIndex()));
}

GeometryIterator<FaceAdjacentVerticesWalker> Face::GetAdjacentVerices() const {
  return GeometryIterator<FaceAdjacentVerticesWalker>(GetHalfedge());
}

GeometryIterator<FaceAdjacentEdgesWalker> Face::GetAdjacentEdges() const {
  return GeometryIterator<FaceAdjacentEdgesWalker>(GetHalfedge());
}

// HALFEDGE
Halfedge::Halfedge(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Halfedge Halfedge::GetNextHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->halfedge(index_).next_);
}

Halfedge Halfedge::GetTwinHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->halfedge(index_).twin_);
}

Vertex Halfedge::GetSourceVertex() const {
  return Vertex(GetGeometry(), GetGeometry()->halfedge(index_).vertex_);
}

Vertex Halfedge::GetTargetVertex() const {
  return GetNextHalfedge().GetSourceVertex();
}

Halfedge Halfedge::GetNextOutgoingNeighbor() const {
  return GetTwinHalfedge().GetNextHalfedge();
}

Edge Halfedge::GetEdge() const {
  return Edge(GetGeometry(), GetGeometry()->halfedge(GetIndex()).edge_);
}

Face Halfedge::GetFace() const {
  return Face(GetGeometry(), GetGeometry()->halfedge(GetIndex()).face_);
}

} // namespace Algernon