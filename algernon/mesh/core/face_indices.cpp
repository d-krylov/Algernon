#include "algernon/mesh/include/face_indices.h"

namespace Algernon {

FaceIndices::FaceIndices(std::span<const IndexType> indices) : indices_(indices.begin(), indices.end()) {
}

FaceIndices::FaceIndices(std::initializer_list<IndexType> indices) : indices_(indices) {
}

FaceIndices::FaceIndices(IndexType i0, IndexType i1, IndexType i2) : indices_{i0, i1, i2} {
}

std::size_t FaceIndices::size() const {
  return indices_.size();
}

std::vector<IndexType>::iterator FaceIndices::begin() {
  return indices_.begin();
}

std::vector<IndexType>::const_iterator FaceIndices::begin() const {
  return indices_.cbegin();
}

std::vector<IndexType>::iterator FaceIndices::end() {
  return indices_.end();
}

std::vector<IndexType>::const_iterator FaceIndices::end() const {
  return indices_.cend();
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