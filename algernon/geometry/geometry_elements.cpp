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

Vertex::Vertex(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
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

Edge::Edge(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Face::Face(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Halfedge::Halfedge(const Geometry *geometry, IndexType index) : GeometryElement(geometry, index) {
}

Vertex Edge::GetSourceVertex() const {
}

Vertex Edge::GetTargetVertex() const {
}

Halfedge Edge::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->edge(GetIndex()));
}

Halfedge Vertex::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->vertex(GetIndex()));
}

Halfedge Face::GetHalfedge() const {
  return Halfedge(GetGeometry(), GetGeometry()->face(GetIndex()));
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