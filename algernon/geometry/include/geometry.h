#ifndef ALGERNON_GEOMETRY_H
#define ALGERNON_GEOMETRY_H

#include "geometry_elements.h"
#include <vector>
#include <span>

namespace Algernon {

class FaceIndices;

struct GeometryStatistics {
  IndexType halfedges_{0};
  IndexType vertices_{0};
  IndexType faces_{0};
  IndexType edges_{0};
};

class Geometry {
public:
  struct halfedge_t {
    bool operator==(const halfedge_t &) const = default;

    IndexType vertex_{INVALID_INDEX}; // start vertex of a half-edge
    IndexType face_{INVALID_INDEX};   // incident face of a half-edge
    IndexType next_{INVALID_INDEX};   // the next half-edge on the face in counter-clockwise order
    IndexType edge_{INVALID_INDEX};
    IndexType twin_{INVALID_INDEX};
  };

public:
  Geometry(std::span<const FaceIndices> faces);

  bool UsesImplicitTwin() const;

  std::span<const halfedge_t> GetHalfedges() const;
  std::span<const IndexType> GetFaceIndices() const;
  std::span<const IndexType> GetEdgeIndices() const;
  std::span<const IndexType> GetVertexIndices() const;

protected:
  void Allocate(std::span<const FaceIndices> faces);

  void BuildImplicit(std::span<const FaceIndices> faces);
  void BuildExplicit(std::span<const FaceIndices> faces);

  static IndexType GetTwinIndexImplicit(IndexType he_index);
  static IndexType GetEdgeIndexImplicit(IndexType he_index);
  static IndexType GetHalfedgeIndexImplicit(IndexType edge_index);

  halfedge_t halfedge(IndexType index) const;
  IndexType face(IndexType index) const;
  IndexType edge(IndexType index) const;
  IndexType vertex(IndexType index) const;

private:
  GeometryStatistics geometry_statistics_;
  std::vector<halfedge_t> halfedges_;
  std::vector<IndexType> he_edges_;       // edge index for halfedge. For explicit
  std::vector<IndexType> he_twins_;       // twin index for halfedge. For explicit
  std::vector<IndexType> face_indices_;   // index into halfedges_ for some halfedge belonging to a face
  std::vector<IndexType> edge_indices_;   // index into halfedges_ for some halfedge belonging to a edge
  std::vector<IndexType> vertex_indices_; // index into halfedges_ for some halfedge emanating from a vertex

  bool uses_implicit_twin_ = false;

  // FRIENDS
  friend class Vertex;
  friend class Edge;
  friend class Face;
  friend class Halfedge;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_H