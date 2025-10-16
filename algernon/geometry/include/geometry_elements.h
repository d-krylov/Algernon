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
class EdgeAdjacentFacesWalker;
class FaceAdjacentVerticesWalker;
class FaceAdjacentEdgesWalker;
class FaceAdjacentHalfedgesWalker;

class GeometryElement {
public:
  GeometryElement() = default;

  GeometryElement(const Geometry *geometry, IndexType index);

  IndexType GetIndex() const;

  operator IndexType() const;

  virtual bool IsValid() const;

  const Geometry *GetGeometry() const;

  std::strong_ordering operator<=>(const GeometryElement &other) const;

  bool operator==(const GeometryElement &) const = default;

protected:
  const Geometry *geometry_{nullptr};
  IndexType index_{INVALID_INDEX};
};

class Vertex : public GeometryElement {
public:
  Vertex() = default;

  bool IsValid() const override;

  Vertex(const Geometry *geometry, IndexType index);

  GeometryIterator<VertexAdjacentVerticesWalker> GetAdjacentVertices() const;
  GeometryIterator<VertexAdjacentEdgesWalker> GetAdjacentEdges() const;
  GeometryIterator<VertexAdjacentFacesWalker> GetAdjacentFaces() const;

  Halfedge GetHalfedge() const;
  std::size_t GetEdgeDegree() const;
  std::size_t GetFaceDegree() const;
  bool IsBoundary() const;
};

class Edge : public GeometryElement {
public:
  Edge() = default;

  Edge(const Geometry *geometry, IndexType index);

  Vertex GetSourceVertex() const;
  Vertex GetTargetVertex() const;
  bool IsBoundary() const;

  GeometryIterator<EdgeAdjacentFacesWalker> GetAdjacentFaces() const;

  Halfedge GetHalfedge() const;
};

class Face : public GeometryElement {
public:
  Face() = default;

  Face(const Geometry *geometry, IndexType index);

  bool IsValid() const override;

  GeometryIterator<FaceAdjacentEdgesWalker> GetAdjacentEdges() const;
  GeometryIterator<FaceAdjacentVerticesWalker> GetAdjacentVertices() const;
  GeometryIterator<FaceAdjacentHalfedgesWalker> GetAdjacentHalfedges() const;

  std::size_t GetDegree() const;
  Halfedge GetHalfedge() const;
  bool IsBoundary() const;
};

class Halfedge : public GeometryElement {
public:
  Halfedge() = default;

  Halfedge(const Geometry *geometry, IndexType index);

  bool IsBoundary() const;
  Halfedge GetTwinHalfedge() const;
  Halfedge GetNextHalfedge() const;
  Halfedge GetPreviousHalfedge() const;
  Halfedge GetPreviousOutgoingNeighbor() const;
  Halfedge GetNextOutgoingNeighbor() const;
  Halfedge GetNextIncomingNeighbor() const;
  Vertex GetSourceVertex() const;
  Vertex GetTargetVertex() const;
  Edge GetEdge() const;
  Face GetFace() const;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_ELEMENTS_H