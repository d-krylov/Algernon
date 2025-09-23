#ifndef ALGERNON_POLYGON_H
#define ALGERNON_POLYGON_H

#include "algernon/mathematics/include/mathematics_types.h"
#include <vector>
#include <span>

namespace Algernon {

class FaceIndices;

class Polygon {
public:
  Polygon(std::span<const Vector3f> points);
  Polygon(std::span<const Vector3f> points, const FaceIndices &face);

  std::size_t size() const;

  bool IsConvex() const;

  Vector3f GetU() const;
  Vector3f GetV() const;

  Vector3f GetCentroid() const;

  std::vector<Vector3f>::iterator begin();
  std::vector<Vector3f>::const_iterator begin() const;
  std::vector<Vector3f>::iterator end();
  std::vector<Vector3f>::const_iterator end() const;

private:
  std::vector<Vector3f> vertices_;
};

} // namespace Algernon

#endif // ALGERNON_POLYGON_H