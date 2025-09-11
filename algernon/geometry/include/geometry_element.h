#ifndef ALGERNON_GEOMETRY_ELEMENT_H
#define ALGERNON_GEOMETRY_ELEMENT_H

#include "algernon/core/include/core_types.h"

namespace Algernon {

class Geometry;
class Halfedge;

class GeometryElement {
public:
  GeometryElement(const Geometry *geometry, IndexType index);

  IndexType GetIndex() const;

protected:
  const Geometry *geometry_{nullptr};
  IndexType index_{INVALID_INDEX};
};

class GeometryVertex : public GeometryElement {
public:
  GeometryVertex(const Geometry *geometry, IndexType index);

  Halfedge GetHaledge() const;
};

class GeometryEdge : public GeometryElement {
public:
  GeometryEdge(const Geometry *geometry, IndexType index);

  Halfedge GetHaledge() const;
};

struct GeometryFace : public GeometryElement {
public:
  GeometryFace(const Geometry *geometry, IndexType index);

  Halfedge GetHaledge() const;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_ELEMENT_H