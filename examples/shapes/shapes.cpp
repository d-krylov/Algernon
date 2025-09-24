#include "algernon/common/algernon.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include <print>
#include <chrono>
#include <cassert>

using namespace Algernon;

int main() {

  polyscope::init();

  auto sdf = [&](Vector3f p) {
    p = OperationTwist(p, 0.5f);
    auto s1 = SDBox(p, 1.0f, 1.0f, 1.0f);
    return s1;
  };

#if 0
  auto vertices = TriangulateGrid(sdf, Vector3f(-3.0f), Vector3f(3.0f), Vector3f(300), 0.001f);

  std::vector<std::vector<uint32_t>> indices;

  for (auto i = 0; i < vertices.size(); i += 3) {
    auto &t = indices.emplace_back();
    t.emplace_back(i);
    t.emplace_back(i + 1);
    t.emplace_back(i + 2);
  }
#endif

  // Mesh mesh("../../Models/bunny.obj");

  // auto smooth = LaplacianSmoothing(mesh.GetVertices(), mesh.GetFaces(), 7);

  auto polyhedron = Polyhedron::MakeIcosahedron();

  Geometry geometry(polyhedron.GetFaces());

  auto polyscope_mesh = polyscope::registerSurfaceMesh("my mesh", polyhedron.GetVertices(), geometry.GetFaceIndices());

  // polyscope_mesh->addVertexColorQuantity("vertex colors", mesh.GetColors());

  polyscope::show();

  return 0;
}