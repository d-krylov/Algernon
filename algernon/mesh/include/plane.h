#ifndef ALGERNON_PLANE_H
#define ALGERNON_PLANE_H

#include "algernon/mathematics/include/mathematics_types.h"

namespace Algernon {

class Plane {
public:
  Plane(const Vector3f normal, float offset);

  Plane(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2);

  const Vector3f &GetNormal() const;

  float GetOffset() const;

  float GetSignedDistance(const Vector3f &point) const;

private:
  Vector3f normal_;
  float offset_;
};

} // namespace Algernon

#endif // ALGERNON_PLANE_H