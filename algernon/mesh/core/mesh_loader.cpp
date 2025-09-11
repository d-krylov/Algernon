#include "algernon/mesh/include/mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace Algernon {

std::vector<Vector3f> GetMeshVertices(const tinyobj::ObjReader &reader) {
  std::vector<Vector3f> out;
  const auto &attributes = reader.GetAttrib();
  for (auto v = 0; v < attributes.vertices.size(); v += 3) {
    auto x = attributes.vertices[v + 0];
    auto y = attributes.vertices[v + 1];
    auto z = attributes.vertices[v + 2];
    out.emplace_back(x, y, z);
  }
  return out;
}

std::vector<Face> GetMeshFaces(const tinyobj::ObjReader &reader) {
  std::vector<Face> out;
  const auto &shapes = reader.GetShapes();
  for (const auto &shape : shapes) {
    for (auto i = 0; i < shape.mesh.indices.size(); i += 3) {
      auto i0 = shape.mesh.indices[i + 0];
      auto i1 = shape.mesh.indices[i + 1];
      auto i2 = shape.mesh.indices[i + 2];
      out.emplace_back(i0.vertex_index, i1.vertex_index, i2.vertex_index);
    }
  }
  return out;
}

void Mesh::Load(const std::filesystem::path &path) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig reader_config;

  auto status = reader.ParseFromFile(path.string(), reader_config);

  vertices_ = GetMeshVertices(reader);
  faces_ = GetMeshFaces(reader);
  colors_ = std::vector<Vector3f>(vertices_.size(), Vector3f(0.5f, 0.5f, 0.0f));
}

} // namespace Algernon