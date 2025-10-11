#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include "algernon/mesh/include/face_indices.h"

namespace Algernon {

bool Geometry::UsesImplicitTwin() const {
  return uses_implicit_twin_;
}

// IMPLICIT GEOMETRY

// clang-format off
IndexType Geometry::GetTwinIndexImplicit(IndexType he_index) { return he_index ^ 1; }
IndexType Geometry::GetEdgeIndexImplicit(IndexType he_index) { return he_index / 2; }
IndexType Geometry::GetHalfedgeIndexImplicit(IndexType edge_index) { return edge_index * 2; }
// clang-format on

// FOR GEOMETRY ELEMENTS

Geometry::halfedge_t Geometry::get_halfedge(IndexType index) const {
  return halfedges_[index];
}

IndexType Geometry::get_face(IndexType index) const {
  return faces_[index];
}

IndexType Geometry::get_edge(IndexType index) const {
  return UsesImplicitTwin() ? GetEdgeIndexImplicit(index) : he_edges_[index];
}

IndexType Geometry::get_twin(IndexType index) const {
  return UsesImplicitTwin() ? GetTwinIndexImplicit(index) : he_twins_[index];
}

IndexType Geometry::get_next_outgoing_neighbor(IndexType index) const {
  return get_halfedge(get_twin(index)).next_;
}

IndexType Geometry::get_next_incoming_neighbor(IndexType index) const {
  return get_twin(get_halfedge(index).next_);
}

IndexType Geometry::vertex(IndexType index) const {
  return vertices_[index];
}

// SAFE CREATORS

Halfedge Geometry::CreateHalfedge(IndexType vertex, IndexType face, IndexType next) {
  auto implicit = UsesImplicitTwin();

  halfedges_.emplace_back(vertex, face, next);

  if (implicit == false) {
    he_edges_.emplace_back(INVALID_INDEX);
    he_twins_.emplace_back(INVALID_INDEX);
  }

  return Halfedge(this, GetHalfedgesSize() - 1);
}

Halfedge Geometry::CreateEdge() {
  auto implicit = UsesImplicitTwin();

  halfedges_.emplace_back(INVALID_INDEX, INVALID_INDEX, INVALID_INDEX);
  halfedges_.emplace_back(INVALID_INDEX, INVALID_INDEX, INVALID_INDEX);

  if (implicit == false) {
    he_edges_.emplace_back(INVALID_INDEX);
    he_twins_.emplace_back(INVALID_INDEX);
  }

  return Halfedge(this, GetHalfedgesSize() - 2);
}

Vertex Geometry::CreateVertex(IndexType he_index) {
  vertices_.emplace_back(he_index);
  return Vertex(this, GetVerticesSize() - 1);
}

Face Geometry::CreateFace(IndexType he_index) {
  faces_.emplace_back(he_index);
  return Face(this, GetFacesSize() - 1);
}

// PUBLIC API

Halfedge Geometry::GetHalfedge(IndexType index) const {
  return Halfedge(this, index);
}

Vertex Geometry::GetVertex(IndexType index) const {
  return Vertex(this, index);
}

Face Geometry::GetFace(IndexType index) const {
  return Face(this, index);
}

Edge Geometry::GetEdge(IndexType index) const {
  return Edge(this, index);
}

std::size_t Geometry::GetNumberHalfedges() const {
  return halfedges_.size();
}

std::size_t Geometry::GetNumberVertices() const {
  return GetVerticesSize() - geometry_statistics_.number_delered_vertices_;
}

std::size_t Geometry::GetNumberFaces() const {
  return GetVerticesSize() - geometry_statistics_.number_delered_faces_;
}

std::size_t Geometry::GetNumberEdges() const {
  return UsesImplicitTwin() ? GetHalfedgesSize() / 2 : GetEdgesSize();
}

// clang-format off
std::size_t Geometry::GetHalfedgesSize() const { return halfedges_.size(); }
std::size_t Geometry::GetVerticesSize() const { return vertices_.size(); }
std::size_t Geometry::GetFacesSize() const { return faces_.size(); }
std::size_t Geometry::GetEdgesSize() const { return edges_.size(); }
// clang-format on

Geometry::Geometry(std::span<const FaceIndices> faces, bool is_implicit) : uses_implicit_twin_(is_implicit) {
  if (is_implicit) {
    BuildImplicit(faces);
  } else {
    BuildExplicit(faces);
  }
}

std::vector<FaceIndices> Geometry::GetFaceIndices() const {
  std::vector<FaceIndices> out;
  for (const auto &face : GetFaces()) {
    std::vector<IndexType> vertices;
    for (const auto &vertex : face.GetAdjacentVerices()) {
      vertices.emplace_back(vertex.GetIndex());
    }
    out.emplace_back(vertices);
  }
  return out;
}

} // namespace Algernon