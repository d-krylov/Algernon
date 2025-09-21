#include "algernon/mesh/shapes/include/polyhedron.h"
#include "algernon/mathematics/include/bounding_box.h"
#include "algernon/mesh/include/mesh_tools.h"
#include <algorithm>

namespace Algernon {

Polyhedron::Polyhedron(std::span<const Vector3f> vertices, std::span<const Face> faces)
  : vertices_(vertices.begin(), vertices.end()), faces_(faces.begin(), faces.end()) {
}

std::size_t Polyhedron::GetNumberOfVertices() const {
  return vertices_.size();
}

std::size_t Polyhedron::GetNumberOfFaces() const {
  return faces_.size();
}

std::size_t Polyhedron::GetNumberOfEdges() const {
  return GetNumberEdgesInFacesFast(faces_);
}

std::span<const Vector3f> Polyhedron::GetVertices() const {
  return vertices_;
}

std::span<const Face> Polyhedron::GetFaces() const {
  return faces_;
}

Polyhedron Polyhedron::MakeHexahedron() {
  Vector3f min(-1.0f, -1.0f, -1.0f);
  Vector3f max(+1.0f, +1.0f, +1.0f);
  return BoundingBox(min, max).GetPolyhedron();
}

Polyhedron Polyhedron::MakeIcosahedron() {
  auto phi = 0.5f + 0.5f * std::sqrt(5.0f);
  auto a = 0.5f;
  auto b = 0.5f / phi;
  std::vector<Vector3f> vertices{
    {+0, +b, -a}, // CENTER UP FAR
    {+b, +a, +0}, // RIGHT UP CENTER
    {-b, +a, +0}, // LEFT UP CENTER
    {+0, +b, +a}, // CENTER UP NEAR
    {+0, -b, +a}, // CENTER DOWN NEAR
    {-a, +0, +b}, // LEFT CENTER NEAR
    {+a, +0, +b}, // RIGHT CENTER NEAR
    {+0, -b, -a}, // CENTER DOWN FAR
    {-a, +0, -b}, //
    {-b, -a, +0}, //
    {+b, -a, +0}, //
    {+a, +0, -b}  //
  };

  std::vector<Face> faces{
    {0, 1, 2},   //
    {3, 2, 1},   //
    {3, 4, 5},   //
    {3, 6, 4},   //
    {0, 7, 11},  //
    {0, 8, 7},   //
    {4, 10, 9},  //
    {7, 9, 10},  //
    {2, 5, 8},   //
    {9, 8, 5},   //
    {1, 11, 6},  //
    {10, 6, 11}, //
    {3, 5, 2},   //
    {3, 1, 6},   //
    {0, 2, 8},   //
    {0, 11, 1},  //
    {7, 8, 9},   //
    {7, 10, 11}, //
    {4, 9, 5},   //
    {4, 6, 10}   //
  };

  return Polyhedron(vertices, faces);
}

Polyhedron Polyhedron::MakeOctahedron() {
  auto a = 0.5f / std::sqrt(2.0f);
  auto b = 0.5f;

  std::vector<Vector3f> vertices{
    {-a, +0, +a}, // LEFT NEAR
    {+a, +0, +a}, // RIGHT NEAR
    {+a, +0, -a}, // RIGHT FAR
    {-a, +0, -a}, // LEFT FAR
    {+0, +b, +0}, // UP
    {+0, -b, +0}  // DOWN
  };

  std::vector<Face> faces{
    {0, 1, 4}, // UP FRONT
    {1, 2, 4}, // UP RIGHT
    {2, 3, 4}, // UP BACK
    {3, 0, 4}, // UP LEFT
    {0, 5, 1}, // DOWN FRONT
    {1, 5, 2}, // DOWN RIGHT
    {2, 5, 3}, // DOWN BACK
    {3, 5, 0}  // DOWN LEFT
  };

  return Polyhedron(vertices, faces);
}

Polyhedron Polyhedron::MakeTetrahedron() {

  std::vector<Vector3f> vertices{
    {+1, +1, +1}, //
    {-1, +1, -1}, //
    {+1, -1, -1}, //
    {-1, -1, +1}  //
  };

  std::vector<Face> faces{
    {0, 1, 2}, //
    {1, 3, 2}, //
    {3, 0, 2}, //
    {0, 3, 1}  //
  };

  return Polyhedron(vertices, faces);
}

Polyhedron Polyhedron::MakeDodecahedron() {
  auto phi = 0.5f + 0.5f * std::sqrt(5.0f);
  auto b = 1.0f / phi;
  auto c = 2.0f - phi;
  std::vector<Vector3f> vertices{
    {+c, +0, +1}, //
    {-c, +0, +1}, //
    {-b, +b, +b}, //
    {+0, +1, +c}, //
    {+b, +b, +b}, //
    {+b, -b, +b}, //
    {+0, -1, +c}, //
    {-b, -b, +b}, //
    {+0, -1, -c}, //
    {+b, -b, -b}, //
    {-c, +0, -1}, //
    {+c, +0, -1}, //
    {-b, -b, -b}, //
    {+b, +b, -b}, //
    {+0, +1, -c}, //
    {-b, +b, -b}, //
    {+1, +c, +0}, //
    {-1, +c, +0}, //
    {-1, -c, +0}, //
    {+1, -c, +0}  //
  };

  std::vector<Face> faces{
    {0, 1, 2, 3, 4},      //
    {1, 0, 5, 6, 7},      //
    {11, 10, 12, 8, 9},   //
    {10, 11, 13, 14, 15}, //
    {13, 16, 4, 3, 14},   //
    {2, 17, 15, 14, 3},   //
    {12, 18, 7, 6, 8},    //
    {5, 19, 9, 8, 6},     //
    {16, 19, 5, 0, 4},    //
    {19, 16, 13, 11, 9},  //
    {17, 18, 12, 10, 15}, //
    {18, 17, 2, 1, 7}     //
  };

  auto triangulated_faces = TriangulateFaces(faces);

  return Polyhedron(vertices, triangulated_faces);
}

int32_t Polyhedron::GetEulerСharacteristic() const {
  int32_t v = GetNumberOfVertices();
  int32_t f = GetNumberOfFaces();
  int32_t e = GetNumberOfEdges();
  return v + f - e;
}

Polygon Polyhedron::GetFacePolygon(uint32_t face_index) const {
  return Polygon(GetVertices(), faces_[face_index]);
}

Vector3f Polyhedron::GetFaceCentroid(uint32_t face_index) const {
  Vector3f centroid(0.0f);
  const auto &face = faces_[face_index];
  auto number_vertices = static_cast<float>(face.size());
  for (const auto &vertex_index : face) {
    centroid += vertices_[vertex_index];
  }
  return centroid / number_vertices;
}

Vector3f Polyhedron::GetFaceNormal(uint32_t face_index) const {
}

} // namespace Algernon