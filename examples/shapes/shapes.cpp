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
    auto s1 = SDSphere(p, 1.0f);
    return s1;
  };

  auto vertices = TriangulateGrid(sdf, Vector3f(-2.0f), Vector3f(2.0f), Vector3f(100), 0.001f);

  std::vector<FaceIndices> indices;

  for (auto i = 0; i < vertices.size(); i += 3) {
    indices.emplace_back(i, i + 1, i + 2);
  }

  Mesh mesh("../../Models/bunny.obj");

  auto del = GetDelauney(mesh.GetVertices(), mesh.GetFaces());

  auto polyscope_mesh = polyscope::registerSurfaceMesh("my mesh", del.GetVertices(), del.GetFaces());

  // polyscope_mesh->addVertexColorQuantity("vertex colors", mesh.GetColors());

  polyscope::show();

  return 0;
}