#include "algernon/mesh/include/mesh.h"
#include "algernon/mesh/include/mesh_tools.h"

namespace Algernon {

Mesh::Mesh(const std::filesystem::path &path) {
  Load(path);
}

std::span<const Vector3f> Mesh::GetVertices() const {
  return vertices_;
}

std::span<const Face> Mesh::GetFaces() const {
  return faces_;
}

std::span<const Vector3f> Mesh::GetColors() const {
  return colors_;
}

std::size_t Mesh::GetNumberOfVertices() const {
  return vertices_.size();
}

std::size_t Mesh::GetNumberOfFaces() const {
  return faces_.size();
}

std::size_t Mesh::GetNumberOfEdges() const {
  return GetNumberEdgesInFacesSlow(faces_);
}

int32_t Mesh::GetEulerСharacteristic() const {
  int32_t v = GetNumberOfVertices();
  int32_t f = GetNumberOfFaces();
  int32_t e = GetNumberOfEdges();
  return v + f - e;
}

void Mesh::SetVertexColor(IndexType vertex_index, const Vector3f &color) {
  colors_[vertex_index] = color;
}

bool Mesh::IsClosed() const {
}

} // namespace Algernon