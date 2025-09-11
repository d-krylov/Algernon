#include "algernon/mesh/include/face.h"

namespace Algernon {

Face::Face(std::span<const IndexType> indices) : indices_(indices.begin(), indices.end()) {
}

Face::Face(std::initializer_list<IndexType> indices) : indices_(indices) {
}

Face::Face(IndexType i0, IndexType i1, IndexType i2) : indices_{i0, i1, i2} {
}

Index2 Face::GetEdge(IndexType index) const {
  auto i0 = indices_[(index + 0) % size()];
  auto i1 = indices_[(index + 1) % size()];
  return Index2(i0, i1);
}

Index3 Face::GetTriangle(IndexType index) const {
  auto v0 = indices_[0];
  auto v1 = indices_[index + 1];
  auto v2 = indices_[index + 2];
  return Index3(v0, v1, v2);
}

Face Face::GetTriangleFace(IndexType index) const {
  auto v0 = indices_[0];
  auto v1 = indices_[index + 1];
  auto v2 = indices_[index + 2];
  return Face{v0, v1, v2};
}

} // namespace Algernon