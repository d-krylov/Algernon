#include "algernon/common/algernon.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"

using namespace Algernon;

int main() {

  polyscope::init();

  auto sdf = [&](Vector3f p) {
    auto s1 = SDBoxFrame(p - Vector3f(0.0f, 1.0f, 0.0f), 0.5f, 0.5f, 0.5f, 0.1f);
    auto s2 = SDRoundBox(p - Vector3f(0.0f, 0.0f, 0.0f), 0.5f, 0.5f, 0.5f, 0.1f);
    auto s3 = SDVerticalCapsule(p - Vector3f(0.0f, 1.0f, 0.0f), 1.0f, 0.5f);
    auto s4 = SDTorus(p - Vector3f(0.0f, 2.0f, 0.0f), 1.0f, 0.2f);
    auto s5 = SDRoundedCylinder(p, 0.3f, 0.1f, 0.5f);
    return OperationUnion(std::array{s3, s4, s5});
  };

  auto vertices = TriangulateGrid(sdf, Vector3f(-3.0f), Vector3f(3.0f), Vector3f(300), 0.001f);

  std::vector<std::vector<uint32_t>> indices;

  for (auto i = 0; i < vertices.size(); i += 3) {
    auto &t = indices.emplace_back();
    t.emplace_back(i);
    t.emplace_back(i + 1);
    t.emplace_back(i + 2);
  }

  auto polyscope_mesh = polyscope::registerSurfaceMesh("my mesh", vertices, indices);

  polyscope::show();

  return 0;
}