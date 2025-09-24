#ifndef ALGERNON_FACE_INDICES_H
#define ALGERNON_FACE_INDICES_H

#include "algernon/core/include/core_types.h"
#include <vector>
#include <span>

namespace Algernon {

class FaceIndices {
public:
  FaceIndices(std::span<const IndexType> indices);

  FaceIndices(std::initializer_list<IndexType> indices);

  FaceIndices(IndexType i0, IndexType i1, IndexType i2);

  std::size_t size() const;

  std::vector<IndexType>::iterator begin();

  std::vector<IndexType>::iterator end();

  std::vector<IndexType>::const_iterator begin() const;

  std::vector<IndexType>::const_iterator end() const;

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