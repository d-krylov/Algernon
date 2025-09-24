#include "conway.h"
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

void OperatorDUAL(const Polyhedron &polyhedron) {
}

void OperatorAMBO(const Polyhedron &polyhedron) {
}

} // namespace Algernon