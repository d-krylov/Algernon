#ifndef ALGERNON_FACE_INDICES_H
#define ALGERNON_FACE_INDICES_H

#include "algernon/core/include/core_types.h"
#include <vector>
#include <span>
#include <ranges>
#include <functional>

namespace Algernon {

class FaceIndices {
public:
  FaceIndices(std::span<const IndexType> indices);

  FaceIndices(std::initializer_list<IndexType> indices);

  FaceIndices(IndexType i0, IndexType i1, IndexType i2);

  auto size() const;

  auto begin();

  auto begin() const;

  auto end();

  auto end() const;

  auto GetEdgeView() const;

  auto GetTriangleView() const;

  auto GetTriangleFaceView() const;

  Index2 GetEdge(IndexType index) const;

  Index3 GetTriangle(IndexType index) const;

  FaceIndices GetTriangleFace(IndexType index) const;

private:
  std::vector<IndexType> indices_;
};

} // namespace Algernon

#include "face_indices.ipp"

#endif // ALGERNON_FACE_INDICES_H