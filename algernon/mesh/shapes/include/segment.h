#ifndef ALGERNON_SEGMENT_H
#define ALGERNON_SEGMENT_H

#include "algernon/mathematics/include/mathematics_types.h"

namespace Algernon {

class Segment {
public:
  Segment(const Vector3f &p0, const Vector3f &p1);

  Vector3f GetPoint(float d) const;

private:
  Vector3f p0_;
  Vector3f p1_;
};

} // namespace Algernon

#endif // ALGERNON_SEGMENT_H