#ifndef ALGERNON_GEOMETRY_H
#define ALGERNON_GEOMETRY_H

#include "algernon/mesh/include/face.h"
#include "geometry_element.h"
#include <vector>

namespace Algernon {

struct GeometryStatistics {
  IndexType halfedges_{0};
  IndexType vertices_{0};
  IndexType faces_{0};
  IndexType edges_{0};
};

class Geometry {
public:
  //
  struct halfedge_t {
    bool operator==(const halfedge_t &) const = default;

    IndexType vertex_{INVALID_INDEX}; // start vertex of a half-edge
    IndexType face_{INVALID_INDEX};   // incident face of a half-edge
    IndexType next_{INVALID_INDEX};   // the next half-edge on the face in counter-clockwise order
    IndexType edge_{INVALID_INDEX};   // optional for implicit
    IndexType twin_{INVALID_INDEX};   // optional for implicit
  };

public:
  Geometry(std::span<const Face> faces);

  bool UsesImplicitTwin() const;

  std::span<const halfedge_t> GetHalfedges() const;
  std::span<const IndexType> GetFaceIndices() const;
  std::span<const IndexType> GetEdgeIndices() const;
  std::span<const IndexType> GetVertexIndices() const;

protected:
  void Allocate(std::span<const Face> faces);

  void BuildImplicit(std::span<const Face> faces);
  void BuildExplicit(std::span<const Face> faces);

  static IndexType GetTwinIndexImplicit(IndexType he_index);
  static IndexType GetEdgeIndexImplicit(IndexType he_index);
  static IndexType GetHalfedgeIndexImplicit(IndexType edge_index);

private:
  GeometryStatistics geometry_statistics_;
  std::vector<halfedge_t> he_information_;
  std::vector<IndexType> he_face_indices_;   // index into halfedges_ for some halfedge belonging to a face
  std::vector<IndexType> he_edge_indices_;   // index into halfedges_ for some halfedge belonging to a edge
  std::vector<IndexType> he_vertex_indices_; // index into halfedges_ for some halfedge emanating from a vertex

  bool uses_implicit_twin_ = false;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_H