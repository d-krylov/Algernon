#include "conway.h"
#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include <ranges>

namespace Algernon {

Polyhedron OperatorKIS(const Polyhedron &polyhedron) {
  auto in_faces = polyhedron.GetFaces();
  auto in_vertices = polyhedron.GetVertices();
  std::vector<Vector3f> out_vertices(in_vertices.begin(), in_vertices.end());
  std::vector<FaceIndices> out_faces;
  for (const auto &[face_index, face] : std::views::enumerate(in_faces)) {
    out_vertices.emplace_back(polyhedron.GetFaceCentroid(face_index));
    auto center_index = out_vertices.size() - 1;
    for (const auto &edge : face.GetEdgeView()) {
      out_faces.emplace_back(edge.i0, edge.i1, center_index);
    }
  }
  return Polyhedron(out_vertices, out_faces);
}

Polyhedron OperatorDUAL(const Polyhedron &polyhedron) {
  auto in_faces = polyhedron.GetFaces();
  auto in_vertices = polyhedron.GetVertices();
  std::vector<Vector3f> out_vertices;
  std::vector<FaceIndices> out_faces;
  for (const auto &[face_index, face] : std::views::enumerate(in_faces)) {
    out_vertices.emplace_back(polyhedron.GetFaceCentroid(face_index));
  }
  Geometry geometry(in_faces);
  for (const auto &vertex : geometry.GetVertices()) {
    std::vector<IndexType> out_face;
    for (const auto &face : vertex.GetAdjacentFaces()) {
      out_face.emplace_back(face.GetIndex());
    }
    out_faces.emplace_back(out_face);
  }
  return Polyhedron(out_vertices, out_faces);
}

Polyhedron OperatorExpand(const Polyhedron &polyhedron, float alpha) {
}

void OperatorAMBO(const Polyhedron &polyhedron) {
}

} // namespace Algernon