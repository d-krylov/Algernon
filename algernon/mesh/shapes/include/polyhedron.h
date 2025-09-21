#ifndef ALGERNON_POLYHEDRON_H
#define ALGERNON_POLYHEDRON_H

#include "algernon/mesh/include/face.h"
#include "polygon.h"

namespace Algernon {

// Polyhedron is closed surface composed of polygons
class Polyhedron {
public:
  Polyhedron(std::span<const Vector3f> vertices, std::span<const Face> faces);

  std::span<const Vector3f> GetVertices() const;
  std::span<const Face> GetFaces() const;

  int32_t GetEulerСharacteristic() const;

  std::size_t GetNumberOfVertices() const;
  std::size_t GetNumberOfFaces() const;
  std::size_t GetNumberOfEdges() const;

  Polygon GetFacePolygon(uint32_t face_index) const;

  Vector3f GetFaceCentroid(uint32_t face_index) const;
  Vector3f GetFaceNormal(uint32_t face_index) const;

  static Polyhedron MakeHexahedron();
  static Polyhedron MakeIcosahedron();
  static Polyhedron MakeOctahedron();
  static Polyhedron MakeTetrahedron();
  static Polyhedron MakeDodecahedron();

private:
  std::vector<Face> faces_;
  std::vector<Vector3f> vertices_;
};

} // namespace Algernon

#endif // ALGERNON_POLYHEDRON_H