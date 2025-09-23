#ifndef ALGERNON_GEOMETRY_ELEMENTS_H
#define ALGERNON_GEOMETRY_ELEMENTS_H

#include "algernon/core/include/core_types.h"
#include "geometry_element_iterator.h"

namespace Algernon {

class Geometry;
class Halfedge;
class VertexAdjacentVerticesWalker;
class VertexAdjacentEdgesWalker;
class VertexAdjacentFacesWalker;

class GeometryElement {
public:
  GeometryElement(const Geometry *geometry, IndexType index);

  bool IsValid() const;

  IndexType GetIndex() const;

  const Geometry *GetGeometry() const;

  std::strong_ordering operator<=>(const GeometryElement &other) const;

  bool operator==(const GeometryElement &) const = default;

protected:
  const Geometry *geometry_{nullptr};
  IndexType index_{INVALID_INDEX};
};

class Vertex : public GeometryElement {
public:
  Vertex(const Geometry *geometry, IndexType index);

  GeometryIterator<VertexAdjacentVerticesWalker> GetAdjacentVertices() const;
  GeometryIterator<VertexAdjacentEdgesWalker> GetAdjacentEdges() const;
  GeometryIterator<VertexAdjacentFacesWalker> GetAdjacentFaces() const;

  Halfedge GetHalfedge() const;
  std::size_t GetDegree() const;
};

class Edge : public GeometryElement {
public:
  Edge(const Geometry *geometry, IndexType index);

  Vertex GetSourceVertex() const;
  Vertex GetTargetVertex() const;

  Halfedge GetHalfedge() const;
};

class Face : public GeometryElement {
public:
  Face(const Geometry *geometry, IndexType index);

  Halfedge GetHalfedge() const;
};

class Halfedge : public GeometryElement {
public:
  Halfedge(const Geometry *geometry, IndexType index);

  Halfedge GetTwinHalfedge() const;
  Halfedge GetNextHalfedge() const;
  Halfedge GetNextOutgoingNeighbor() const;
  Vertex GetSourceVertex() const;
  Vertex GetTargetVertex() const;
  Edge GetEdge() const;
  Face GetFace() const;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_ELEMENTS_H