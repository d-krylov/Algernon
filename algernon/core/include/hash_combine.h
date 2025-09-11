#ifndef ALGERNON_HASH_COMBINE_H
#define ALGERNON_HASH_COMBINE_H

#include <cstdint>
#include <functional>

// https://github.com/boostorg/container_hash/blob/develop/include/boost/container_hash/hash.hpp

namespace Algernon {

inline uint32_t hash_mix_32(uint32_t x) {
  constexpr uint32_t m1 = 0x21f0aaad;
  constexpr uint32_t m2 = 0x735a2d97;
  x ^= x >> 16;
  x *= m1;
  x ^= x >> 15;
  x *= m2;
  x ^= x >> 15;
  return x;
}

inline uint64_t hash_mix_64(uint64_t x) {
  constexpr uint64_t m = 0xe9846af9b1a615d;
  x ^= x >> 32;
  x *= m;
  x ^= x >> 32;
  x *= m;
  x ^= x >> 28;
  return x;
}

inline std::size_t hash_mix(std::size_t v) {
  if constexpr (sizeof(std::size_t) == 8) {
    return hash_mix_64(v);
  } else {
    return hash_mix_32(v);
  }
}

template <class T> inline void hash_combine(std::size_t &seed, const T &v) {
  seed = hash_mix(seed + 0x9e3779b9 + std::hash<T>()(v));
}

} // namespace Algernon

#endif // ALGERNON_HASH_COMBINE_H