#ifndef ALGERNON_MARCHING_CUBES_H
#define ALGERNON_MARCHING_CUBES_H

#include <span>
#include <vector>
#include <functional>
#include "algernon/mathematics/include/mathematics_types.h"

namespace Algernon {

using GridFunction = std::function<float(const Vector3f &)>;

std::pair<int32_t, int32_t> GetEdgeVetices(int32_t index);
int32_t GetTriangleIndex(int32_t i0, int32_t i1);
int32_t GetEdgeKey(int32_t index);
std::vector<Vector3f> TriangulateGrid(const GridFunction &grid_function, const Vector3f &min, const Vector3f &max, const Vector3u &grid_size,
                                      float iso);

struct GridCell {
  std::array<Vector3f, 8> points_;
  std::array<float, 8> values_;
};

} // namespace Algernon

#endif // ALGERNON_MARCHING_CUBES_H