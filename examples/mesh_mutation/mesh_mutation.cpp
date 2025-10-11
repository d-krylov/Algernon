#include "algernon/common/algernon.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include <print>

using namespace Algernon;

int main() {

  polyscope::init();

  auto polyhedron = Polyhedron::MakeHexahedron();

  std::vector<Vector3f> vertices(polyhedron.GetVertices().begin(), polyhedron.GetVertices().end());

  vertices.emplace_back(Vector3f(0.0f, 0.0f, 2.0f));

  Geometry geometry(polyhedron.GetFaces(), true);

  // geometry.InsertVertexInFace(geometry.GetFace(4));

  //geometry.InsertEdgeInFace(geometry.GetHalfedge(0), geometry.GetHalfedge(4));

  //geometry.InsertVertexInFace(geometry.GetFace(0));

  geometry.InsertVertexOnEdge(geometry.GetEdge(1));

  auto polyscope_mesh = polyscope::registerSurfaceMesh("my mesh", vertices, geometry.GetFaceIndices());

  polyscope::show();

  return 0;
}