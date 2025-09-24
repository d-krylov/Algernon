#include "laplacian_smoothing.h"
#include "algernon/mesh/include/face_indices.h"
#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include <ranges>
#include <print>

namespace Algernon {

std::vector<Vector3f> LaplacianSmoothing(std::span<const Vector3f> vertices, std::span<const FaceIndices> faces, uint32_t repetitions) {
  std::vector<Vector3f> out(vertices.begin(), vertices.end());
  Geometry geometry(faces);
  for (auto i = 0; i < repetitions; i++) {
    for (const auto &[vertex_index, vertex] : std::views::enumerate(geometry.GetVertices())) {
      Vector3f position(0.0f);
      IndexType count = 0;
      for (const auto &adjacent_vertex : vertex.GetAdjacentVertices()) {
        position += out[adjacent_vertex.GetIndex()];
        count++;
      }
      out[vertex_index] = position / static_cast<float>(count);
    }
  }
  return out;
}

} // namespace Algernon