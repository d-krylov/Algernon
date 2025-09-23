#ifndef ALGERNON_MESH_H
#define ALGERNON_MESH_H

#include <filesystem>
#include "algernon/mathematics/include/mathematics_types.h"
#include "face_indices.h"

namespace Algernon {

class Mesh {
public:
  Mesh(const std::filesystem::path &path);

  void SetVertexColor(IndexType vertex_index, const Vector3f &color);

  std::span<const Vector3f> GetVertices() const;
  std::span<const Vector3f> GetColors() const;
  std::span<const FaceIndices> GetFaces() const;

  std::size_t GetNumberOfVertices() const;
  std::size_t GetNumberOfFaces() const;
  std::size_t GetNumberOfEdges() const;

  bool IsClosed() const;

  int32_t GetEulerСharacteristic() const;

protected:
  void LoadWavefront(const std::filesystem::path &path);
  void LoadGLTF(const std::filesystem::path &path);

private:
  std::vector<Vector3f> vertices_;
  std::vector<Vector3f> colors_;
  std::vector<FaceIndices> faces_;
};

} // namespace Algernon

#endif // ALGERNON_MESH_H