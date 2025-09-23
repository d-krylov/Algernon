#include "algernon/mesh/include/face_indices.h"

namespace Algernon {

FaceIndices::FaceIndices(std::span<const IndexType> indices) : indices_(indices.begin(), indices.end()) {
}

FaceIndices::FaceIndices(std::initializer_list<IndexType> indices) : indices_(indices) {
}

FaceIndices::FaceIndices(IndexType i0, IndexType i1, IndexType i2) : indices_{i0, i1, i2} {
}

Index2 FaceIndices::GetEdge(IndexType index) const {
  auto i0 = indices_[(index + 0) % size()]; // Convenient for getting the next edge
  auto i1 = indices_[(index + 1) % size()];
  return Index2(i0, i1);
}

Index3 FaceIndices::GetTriangle(IndexType index) const {
  auto v0 = indices_[0];
  auto v1 = indices_[index + 1];
  auto v2 = indices_[index + 2];
  return Index3(v0, v1, v2);
}

FaceIndices FaceIndices::GetTriangleFace(IndexType index) const {
  auto v0 = indices_[0];
  auto v1 = indices_[index + 1];
  auto v2 = indices_[index + 2];
  return FaceIndices{v0, v1, v2};
}

} // namespace Algernon