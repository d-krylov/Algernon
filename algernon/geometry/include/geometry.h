#ifndef ALGERNON_GEOMETRY_H
#define ALGERNON_GEOMETRY_H

#include "geometry_elements.h"
#include <vector>
#include <span>

namespace Algernon {

class FaceIndices;

struct GeometryStatistics {
  IndexType number_boundary_loops_{0};
  IndexType number_boundary_edges_{0};
  IndexType number_halfedges_{0};
  IndexType number_vertices_{0};
  IndexType number_faces_{0};
  IndexType number_edges_{0};
  IndexType number_delered_vertices_{0};
  IndexType number_delered_faces_{0};
  IndexType number_deleted_edges_{0};
};

class Geometry {
public:
  struct halfedge_t {
    bool operator==(const halfedge_t &) const = default;

    IndexType vertex_{INVALID_INDEX}; // start vertex of a half-edge
    IndexType face_{INVALID_INDEX};   // incident face of a half-edge
    IndexType next_{INVALID_INDEX};   // the next half-edge on the face in counter-clockwise order
  };

public:
  Geometry(std::span<const FaceIndices> faces, bool is_implicit = false);

  bool UsesImplicitTwin() const;

  auto GetHalfedges() const;
  auto GetFaces() const;
  auto GetEdges() const;
  auto GetVertices() const;

  Edge FindEdge(Vertex start, Vertex end) const;

  std::vector<FaceIndices> GetFaceIndices() const;

  Halfedge GetHalfedge(IndexType index) const;
  Vertex GetVertex(IndexType index) const;
  Face GetFace(IndexType index) const;
  Edge GetEdge(IndexType index) const;

  // MUTATION
  void RemoveEdge(Edge edge);
  void InsertVertexInFace(Face face);
  void InsertVertexOnEdge(Edge edge);
  void InsertVertexOnEdgeTriangular(Edge edge);
  void InsertEdgeInFace(Halfedge he1, Halfedge he2);
  bool Flip(const Edge &edge);

  void DeleteFace(Face face);
  void ContractEdgeTriangular(Edge e);

  void Compress();

  std::size_t GetNumberHalfedges() const;
  std::size_t GetNumberVertices() const;
  std::size_t GetNumberFaces() const;
  std::size_t GetNumberEdges() const;

  std::size_t GetHalfedgesSize() const;
  std::size_t GetVerticesSize() const;
  std::size_t GetFacesSize() const;
  std::size_t GetEdgesSize() const;

protected:
  void Allocate(std::span<const FaceIndices> faces);

  void BuildImplicit(std::span<const FaceIndices> faces);
  void BuildExplicit(std::span<const FaceIndices> faces);

  void GetBoundaryLoops();

  // COMPRESS HELPERS
  void CompressVertices();
  void CompressFaces();
  void CompressEdges();
  void CompressHalfedges();

  // IMPLICIT GEOMETRY
  static IndexType GetTwinIndexImplicit(IndexType he_index);
  static IndexType GetEdgeIndexImplicit(IndexType he_index);
  static IndexType GetHalfedgeIndexImplicit(IndexType edge_index);

  // SAFE CREATORS
  Halfedge CreateHalfedge(IndexType vertex = INVALID_INDEX, IndexType face = INVALID_INDEX, IndexType next = INVALID_INDEX);
  Halfedge CreateEdge();
  Vertex CreateVertex(IndexType he_index = INVALID_INDEX);
  Face CreateFace(IndexType he_index = INVALID_INDEX);

  bool IsVertexValid(IndexType vertex_index) const;
  bool IsFaceValid(IndexType vertex_index) const;

  // FOR GEOMETRY ELEMENTS
  halfedge_t get_halfedge(IndexType index) const;
  IndexType get_face(IndexType index) const;
  IndexType get_edge(IndexType index) const;
  IndexType get_twin(IndexType index) const;
  IndexType get_vertex(IndexType index) const;

  IndexType get_next_outgoing_neighbor(IndexType index) const;
  IndexType get_next_incoming_neighbor(IndexType index) const;

private:
  GeometryStatistics geometry_statistics_;
  std::vector<halfedge_t> halfedges_;
  std::vector<IndexType> he_edges_; // edge index for halfedge. For explicit
  std::vector<IndexType> he_twins_; // twin index for halfedge. For explicit
  std::vector<IndexType> faces_;    // index into halfedges_ for some halfedge belonging to a face
  std::vector<IndexType> edges_;    // index into halfedges_ for some halfedge belonging to a edge
  std::vector<IndexType> vertices_; // index into halfedges_ for some halfedge emanating from a vertex

  bool uses_implicit_twin_ = false;

  // FRIENDS
  friend class Vertex;
  friend class Edge;
  friend class Face;
  friend class Halfedge;
};

} // namespace Algernon

#include "geometry.ipp"

#endif // ALGERNON_GEOMETRY_H