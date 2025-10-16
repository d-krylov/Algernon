#include "algernon/common/algernon.h"
#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include <print>

using namespace Algernon;

int main() {

  polyscope::init();

  auto polyhedron = Polyhedron::MakeHexahedron();

  std::vector<Vector3f> vertices(polyhedron.GetVertices().begin(), polyhedron.GetVertices().end());

  // vertices.emplace_back(Vector3f(1.0f, 0.0f, 1.0f));

  Geometry geometry(polyhedron.GetFaces());

  // geometry.InsertVertexInFace(geometry.GetFace(4));

  // geometry.InsertEdgeInFace(geometry.GetHalfedge(0), geometry.GetHalfedge(4));

  // geometry.InsertVertexInFace(geometry.GetFace(0));

  // geometry.InsertVertexOnEdgeTriangular(geometry.GetEdge(1));

  geometry.RemoveEdge(geometry.GetEdge(1));
  geometry.DeleteFace(geometry.GetFace(0));

  geometry.Compress();


  auto polyscope_mesh = polyscope::registerSurfaceMesh("my mesh", polyhedron.GetVertices(), geometry.GetFaceIndices());

  polyscope::show();

  return 0;
}