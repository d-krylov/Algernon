#include "algernon/core/include/core_types.h"
#include <algorithm>

namespace Algernon {

Index2 Index2::GetSwapped() const {
  return Index2(i1, i0);
}

std::size_t Index2Hash::operator()(const Index2 &index) const {
  auto hash = std::hash<IndexType>()(index.i0);
  hash_combine<IndexType>(hash, index.i1);
  return hash;
}

bool Index2UnorderedComparator::operator()(const Index2 &a, const Index2 &b) const {
  auto [ax, ay] = std::minmax(a.i0, a.i1);
  auto [bx, by] = std::minmax(b.i0, b.i1);
  return std::tie(ax, ay) < std::tie(bx, by);
}

} // namespace Algernon