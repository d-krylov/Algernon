#include "marching_cubes.h"
#include <algorithm>

namespace Algernon {

int32_t GetCubeIndex(const GridCell &cell, float iso) {
  auto cube_index = 0;
  cube_index |= (cell.values_[0] < iso) << 0;
  cube_index |= (cell.values_[1] < iso) << 1;
  cube_index |= (cell.values_[2] < iso) << 2;
  cube_index |= (cell.values_[3] < iso) << 3;
  cube_index |= (cell.values_[4] < iso) << 4;
  cube_index |= (cell.values_[5] < iso) << 5;
  cube_index |= (cell.values_[6] < iso) << 6;
  cube_index |= (cell.values_[7] < iso) << 7;
  return cube_index;
}

Vector3f InterpolateVertex(float iso, const Vector3f &p1, const Vector3f &p2, float v1, float v2) {
  return (std::abs(v2 - v1) < 1e-6f) ? p1 : glm::mix(p1, p2, (iso - v1) / (v2 - v1));
}

std::vector<Vector3f> GetVertices(const GridCell &cell, float iso) {
  std::vector<Vector3f> out(12);
  auto cube_index = GetCubeIndex(cell, iso);
  auto edge_key = GetEdgeKey(cube_index);
  for (auto index = 0; edge_key; index++, edge_key >>= 1) {
    if (edge_key & 1) {
      auto [v0, v1] = GetEdgeVetices(index);
      out[index] = InterpolateVertex(iso, cell.points_[v0], cell.points_[v1], cell.values_[v0], cell.values_[v1]);
    }
  }
  return out;
}

std::vector<Vector3f> GetTriangles(std::span<const Vector3f> vertices, int32_t cube_index) {
  std::vector<Vector3f> triangles;
  for (auto i = 0; GetTriangleIndex(cube_index, i) != -1; i += 3) {
    auto p0 = vertices[GetTriangleIndex(cube_index, i)];
    auto p1 = vertices[GetTriangleIndex(cube_index, i + 1)];
    auto p2 = vertices[GetTriangleIndex(cube_index, i + 2)];
    triangles.emplace_back(p0);
    triangles.emplace_back(p1);
    triangles.emplace_back(p2);
  }
  return triangles;
}

std::vector<Vector3f> TriangulateCell(const GridCell &cell, float iso) {
  auto cube_index = GetCubeIndex(cell, iso);
  auto vertices = GetVertices(cell, iso);
  auto triangles = GetTriangles(vertices, cube_index);
  return triangles;
}

std::vector<Vector3f> TriangulateGrid(const GridFunction &grid_function, const Vector3f &min, const Vector3f &max, const Vector3u &grid_size,
                                      float iso) {
  std::vector<Vector3f> out;
  auto d = (max - min) / Vector3f(grid_size);
  for (auto i = 0; i < grid_size.x; i++) {
    for (auto j = 0; j < grid_size.y; j++) {
      for (auto k = 0; k < grid_size.z; k++) {
        auto point = min + d * Vector3f(i, j, k);
        GridCell grid_cell;
        grid_cell.points_ = {point,
                             point + Vector3f(d.x, 0.0f, 0.0f),
                             point + Vector3f(d.x, 0.0f, d.z),
                             point + Vector3f(0.0f, 0.0f, d.z),
                             point + Vector3f(0.0f, d.y, 0.0f),
                             point + Vector3f(d.x, d.y, 0.0f),
                             point + Vector3f(d.x, d.y, d.z),
                             point + Vector3f(0.0f, d.y, d.z)};

        std::ranges::transform(grid_cell.points_, grid_cell.values_.begin(), grid_function);
        auto triangles = TriangulateCell(grid_cell, iso);
        out.insert(out.end(), triangles.begin(), triangles.end());
      }
    }
  }
  return out;
}

} // namespace Algernon