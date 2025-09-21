#ifndef ALGERNON_SPHERE_H
#define ALGERNON_SPHERE_H

#include "algernon/mathematics/include/mathematics_types.h"
#include "algernon/mesh/include/face.h"
#include <vector>

namespace Algernon {

class Sphere {
public:
  Sphere(const Vector3f &origin, float radius);

  const Vector3f &GetOrigin() const;

  float GetRadius() const;

  std::vector<Vector3f> GetVertices(uint32_t y_sectors, uint32_t xz_sectors) const;

  std::vector<Face> GetFaces(int32_t y_sectors, int32_t xz_sectors) const;

private:
  Vector3f origin_;
  float radius_;
};

} // namespace Algernon

#endif // ALGERNON_SPHERE_H