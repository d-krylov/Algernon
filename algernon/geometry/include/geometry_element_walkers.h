#ifndef ALGERNON_GEOMETRY_ELEMENT_WALKERS_H
#define ALGERNON_GEOMETRY_ELEMENT_WALKERS_H

#include "geometry_elements.h"

namespace Algernon {

// VERTEX WALKERS

class VertexAdjacentVerticesWalker {
public:
  using element_type = Halfedge;
  using return_type = Vertex;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

struct VertexAdjacentEdgesWalker {
  using element_type = Halfedge;
  using return_type = Edge;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

struct VertexAdjacentFacesWalker {
  using element_type = Halfedge;
  using return_type = Face;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

// FACE WALKERS

struct FaceAdjacentVerticesWalker {
  using element_type = Halfedge;
  using return_type = Vertex;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

struct FaceAdjacentEdgesWalker {
  using element_type = Halfedge;
  using return_type = Edge;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

struct FaceAdjacentHalfedgesWalker {
  using element_type = Halfedge;
  using return_type = Halfedge;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

// EDGE WALKERS

struct EdgeAdjacentFacesWalker {
  using element_type = Halfedge;
  using return_type = Face;

  void Advance();

  return_type GetCurrent() const;

  element_type current_element_;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_ELEMENT_WALKERS_H