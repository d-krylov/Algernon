#ifndef ALGERNON_BOUNDING_BOX_H
#define ALGERNON_BOUNDING_BOX_H

#include "mathematics_types.h"

namespace Algernon {

class Polyhedron;

class BoundingBox {
public:
  BoundingBox(const Vector3f &p0, const Vector3f &p1);

  Polyhedron GetPolyhedron() const;

private:
  Vector3f min_;
  Vector3f max_;
};

} // namespace Algernon

#endif // ALGERNON_BOUNDING_BOX_H