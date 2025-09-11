#ifndef ALGERNON_CORE_TYPES_H
#define ALGERNON_CORE_TYPES_H

#include "hash_combine.h"

namespace Algernon {

using IndexType = int32_t;

inline constexpr IndexType INVALID_INDEX = -1;

struct Index2 {

  auto operator<=>(const Index2 &) const = default;

  Index2 GetSwapped() const;

  IndexType i0{INVALID_INDEX};
  IndexType i1{INVALID_INDEX};
};

struct Index3 {

  auto operator<=>(const Index3 &) const = default;

  IndexType i0{INVALID_INDEX};
  IndexType i1{INVALID_INDEX};
  IndexType i2{INVALID_INDEX};
};

struct Index2Hash {
  std::size_t operator()(const Index2 &index) const;
};

struct Index2UnorderedComparator {
  bool operator()(const Index2 &a, const Index2 &b) const;
};

} // namespace Algernon

#endif // ALGERNON_CORE_TYPES_H