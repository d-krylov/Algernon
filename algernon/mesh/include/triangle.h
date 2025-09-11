#ifndef ALGERNON_TRIANGLE_H
#define ALGERNON_TRIANGLE_H

#include "algernon/mathematics/include/mathematics_types.h"

namespace Algernon {

class Triangle {
public:
  Triangle(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2);

  Vector3f GetBarycentricUVW(const Vector3f &p) const;

  Vector3f GetCentroid() const;

private:
  Vector3f p0_;
  Vector3f p1_;
  Vector3f p2_;
};

} // namespace Algernon

#endif // ALGERNON_TRIANGLE_H
