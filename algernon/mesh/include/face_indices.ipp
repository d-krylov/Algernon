#ifndef ALGERNON_FACE_INDICES_IPP
#define ALGERNON_FACE_INDICES_IPP

#include "algernon/core/include/transform_iterator.h"

namespace Algernon {

inline auto FaceIndices::GetEdgeView() const {
  return BaseElements(this, &FaceIndices::GetEdge, size());
}

inline auto FaceIndices::GetTriangleView() const {
  return BaseElements(this, &FaceIndices::GetTriangle, size() - 2);
}

inline auto FaceIndices::GetTriangleFaceView() const {
  return BaseElements(this, &FaceIndices::GetTriangleFace, size() - 2);
}

} // namespace Algernon

#endif // ALGERNON_FACE_INDICES_IPP