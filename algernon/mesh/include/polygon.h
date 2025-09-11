#ifndef ALGERNON_POLYGON_H
#define ALGERNON_POLYGON_H

#include "algernon/mathematics/include/mathematics_types.h"
#include <vector>
#include <span>

namespace Algernon {

class Polygon {
public:
  Polygon(std::span<const Vector3f> points);

  std::size_t GetSize() const;

  bool IsConvex() const;

  Vector3f GetU() const;
  Vector3f GetV() const;

private:
  std::vector<Vector3f> vertices_;
};

} // namespace Algernon

#endif // ALGERNON_POLYGON_H