#include "algernon/common/algernon.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include <print>
#include <chrono>
#include <cassert>

using namespace Algernon;

int main() {

  polyscope::init();

  auto sdf = [&](const Vector3f p) {
    auto s = glm::smoothstep(3.0f, 0.0f, glm::length(Vector2f(p.x, p.z)));
    return p.y - 3.0 * s;
  };

  auto vertices = TriangulateGrid(sdf, Vector3f(-3.0f), Vector3f(3.0f), Vector3f(128), 0.0001f);

  std::vector<std::vector<uint32_t>> indices;

  for (auto i = 0; i < vertices.size(); i += 3) {
    auto &t = indices.emplace_back();
    t.emplace_back(i);
    t.emplace_back(i + 1);
    t.emplace_back(i + 2);
  }

  auto polyscope_mesh = polyscope::registerSurfaceMesh("my mesh", vertices, indices);

  // polyscope_mesh->addVertexColorQuantity("vertex colors", mesh.GetColors());

  polyscope::show();

  return 0;
}