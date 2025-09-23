#include "algernon/common/algernon.h"
#include "gtest/gtest.h"
#include <print>

using namespace Algernon;

TEST(GeometryTest, TetrahedronGeometryExplicit) {
  auto tetrahedron = Polyhedron::MakeTetrahedron();

  Geometry geometry(tetrahedron.GetFaces());

  auto halfedges = geometry.GetHalfedges();
  auto vertices = geometry.GetVertexIndices();
  auto edges = geometry.GetEdgeIndices();
  auto faces = geometry.GetFaceIndices();

  ASSERT_EQ(halfedges[0], Geometry::halfedge_t(0, 0, 1, 0, 11));
  ASSERT_EQ(halfedges[1], Geometry::halfedge_t(1, 0, 2, 1, 5));
  ASSERT_EQ(halfedges[2], Geometry::halfedge_t(2, 0, 0, 2, 7));

  ASSERT_EQ(halfedges[3], Geometry::halfedge_t(1, 1, 4, 3, 10));
  ASSERT_EQ(halfedges[4], Geometry::halfedge_t(3, 1, 5, 4, 8));
  ASSERT_EQ(halfedges[5], Geometry::halfedge_t(2, 1, 3, 1, 1));

  ASSERT_EQ(halfedges[6], Geometry::halfedge_t(3, 2, 7, 5, 9));
  ASSERT_EQ(halfedges[7], Geometry::halfedge_t(0, 2, 8, 2, 2));
  ASSERT_EQ(halfedges[8], Geometry::halfedge_t(2, 2, 6, 4, 4));

  ASSERT_EQ(halfedges[9], Geometry::halfedge_t(0, 3, 10, 5, 6));
  ASSERT_EQ(halfedges[10], Geometry::halfedge_t(3, 3, 11, 3, 3));
  ASSERT_EQ(halfedges[11], Geometry::halfedge_t(1, 3, 9, 0, 0));

  ASSERT_EQ(halfedges[vertices[0]].vertex_, 0);
  ASSERT_EQ(halfedges[vertices[1]].vertex_, 1);
  ASSERT_EQ(halfedges[vertices[2]].vertex_, 2);
  ASSERT_EQ(halfedges[vertices[3]].vertex_, 3);

  ASSERT_EQ(halfedges[faces[0]].face_, 0);
  ASSERT_EQ(halfedges[faces[1]].face_, 1);
  ASSERT_EQ(halfedges[faces[2]].face_, 2);
  ASSERT_EQ(halfedges[faces[3]].face_, 3);

  ASSERT_EQ(halfedges[edges[0]].edge_, 0);
  ASSERT_EQ(halfedges[edges[1]].edge_, 1);
  ASSERT_EQ(halfedges[edges[2]].edge_, 2);
  ASSERT_EQ(halfedges[edges[3]].edge_, 3);
  ASSERT_EQ(halfedges[edges[4]].edge_, 4);
  ASSERT_EQ(halfedges[edges[5]].edge_, 5);
}

TEST(GeometryTest, HexahedronGeometryExplicit) {
  auto hexahedron = Polyhedron::MakeHexahedron();

  Geometry geometry(hexahedron.GetFaces());

  auto halfedges = geometry.GetHalfedges();
  auto vertices = geometry.GetVertexIndices();
  auto edges = geometry.GetEdgeIndices();
  auto faces = geometry.GetFaceIndices();

  Vertex v(&geometry, 1);

  for (auto adj : v.GetAdjacentFaces()) {
    std::println("{}", adj.GetIndex());
  }

  ASSERT_EQ(halfedges[0], Geometry::halfedge_t(0, 0, 1, 0, 22));
  ASSERT_EQ(halfedges[1], Geometry::halfedge_t(1, 0, 2, 1, 7));
  ASSERT_EQ(halfedges[2], Geometry::halfedge_t(2, 0, 3, 2, 16));
  ASSERT_EQ(halfedges[3], Geometry::halfedge_t(3, 0, 0, 3, 13));

  ASSERT_EQ(halfedges[4], Geometry::halfedge_t(1, 1, 5, 4, 21));
  ASSERT_EQ(halfedges[5], Geometry::halfedge_t(5, 1, 6, 5, 11));
  ASSERT_EQ(halfedges[6], Geometry::halfedge_t(6, 1, 7, 6, 17));
  ASSERT_EQ(halfedges[7], Geometry::halfedge_t(2, 1, 4, 1, 1));

  ASSERT_EQ(halfedges[8], Geometry::halfedge_t(5, 2, 9, 7, 20));
  ASSERT_EQ(halfedges[9], Geometry::halfedge_t(4, 2, 10, 8, 15));
  ASSERT_EQ(halfedges[10], Geometry::halfedge_t(7, 2, 11, 9, 18));
  ASSERT_EQ(halfedges[11], Geometry::halfedge_t(6, 2, 8, 5, 5));

  ASSERT_EQ(halfedges[12], Geometry::halfedge_t(4, 3, 13, 10, 23));
  ASSERT_EQ(halfedges[13], Geometry::halfedge_t(0, 3, 14, 3, 3));
  ASSERT_EQ(halfedges[14], Geometry::halfedge_t(3, 3, 15, 11, 19));
  ASSERT_EQ(halfedges[15], Geometry::halfedge_t(7, 3, 12, 8, 9));

  ASSERT_EQ(halfedges[16], Geometry::halfedge_t(3, 4, 17, 2, 2));
  ASSERT_EQ(halfedges[17], Geometry::halfedge_t(2, 4, 18, 6, 6));
  ASSERT_EQ(halfedges[18], Geometry::halfedge_t(6, 4, 19, 9, 10));
  ASSERT_EQ(halfedges[19], Geometry::halfedge_t(7, 4, 16, 11, 14));

  ASSERT_EQ(halfedges[20], Geometry::halfedge_t(4, 5, 21, 7, 8));
  ASSERT_EQ(halfedges[21], Geometry::halfedge_t(5, 5, 22, 4, 4));
  ASSERT_EQ(halfedges[22], Geometry::halfedge_t(1, 5, 23, 0, 0));
  ASSERT_EQ(halfedges[23], Geometry::halfedge_t(0, 5, 20, 10, 12));

  ASSERT_EQ(halfedges[vertices[0]].vertex_, 0);
  ASSERT_EQ(halfedges[vertices[1]].vertex_, 1);
  ASSERT_EQ(halfedges[vertices[2]].vertex_, 2);
  ASSERT_EQ(halfedges[vertices[3]].vertex_, 3);
  ASSERT_EQ(halfedges[vertices[4]].vertex_, 4);
  ASSERT_EQ(halfedges[vertices[5]].vertex_, 5);
  ASSERT_EQ(halfedges[vertices[6]].vertex_, 6);
  ASSERT_EQ(halfedges[vertices[7]].vertex_, 7);

  ASSERT_EQ(halfedges[faces[0]].face_, 0);
  ASSERT_EQ(halfedges[faces[1]].face_, 1);
  ASSERT_EQ(halfedges[faces[2]].face_, 2);
  ASSERT_EQ(halfedges[faces[3]].face_, 3);
  ASSERT_EQ(halfedges[faces[4]].face_, 4);
  ASSERT_EQ(halfedges[faces[5]].face_, 5);

  ASSERT_EQ(halfedges[edges[0]].edge_, 0);
  ASSERT_EQ(halfedges[edges[1]].edge_, 1);
  ASSERT_EQ(halfedges[edges[2]].edge_, 2);
  ASSERT_EQ(halfedges[edges[3]].edge_, 3);
  ASSERT_EQ(halfedges[edges[4]].edge_, 4);
  ASSERT_EQ(halfedges[edges[5]].edge_, 5);
  ASSERT_EQ(halfedges[edges[6]].edge_, 6);
  ASSERT_EQ(halfedges[edges[7]].edge_, 7);
}