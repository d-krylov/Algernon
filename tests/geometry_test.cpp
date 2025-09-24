#include "algernon/common/algernon.h"
#include "gtest/gtest.h"
#include <print>

using namespace Algernon;

struct HalfedgeInformation {
  bool operator==(const HalfedgeInformation &) const = default;

  IndexType vertex_{INVALID_INDEX};
  IndexType face_{INVALID_INDEX};
  IndexType next_{INVALID_INDEX};
  IndexType edge_{INVALID_INDEX};
  IndexType twin_{INVALID_INDEX};
};

HalfedgeInformation MakeHalfedge(Halfedge halfedge) {
  HalfedgeInformation out;
  out.vertex_ = halfedge.GetSourceVertex().GetIndex();
  out.next_ = halfedge.GetNextHalfedge().GetIndex();
  out.twin_ = halfedge.GetTwinHalfedge().GetIndex();
  out.face_ = halfedge.GetFace().GetIndex();
  out.edge_ = halfedge.GetEdge().GetIndex();
  return out;
}

TEST(GeometryTest, TetrahedronGeometryExplicit) {
  auto tetrahedron = Polyhedron::MakeTetrahedron();

  Geometry geometry(tetrahedron.GetFaces());

  auto halfedges = geometry.GetHalfedges();

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(0)), HalfedgeInformation(0, 0, 1, 0, 11));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(1)), HalfedgeInformation(1, 0, 2, 1, 5));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(2)), HalfedgeInformation(2, 0, 0, 2, 7));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(3)), HalfedgeInformation(1, 1, 4, 3, 10));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(4)), HalfedgeInformation(3, 1, 5, 4, 8));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(5)), HalfedgeInformation(2, 1, 3, 1, 1));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(6)), HalfedgeInformation(3, 2, 7, 5, 9));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(7)), HalfedgeInformation(0, 2, 8, 2, 2));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(8)), HalfedgeInformation(2, 2, 6, 4, 4));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(9)), HalfedgeInformation(0, 3, 10, 5, 6));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(10)), HalfedgeInformation(3, 3, 11, 3, 3));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(11)), HalfedgeInformation(1, 3, 9, 0, 0));

  ASSERT_EQ(geometry.GetVertex(0).GetHalfedge().GetSourceVertex().GetIndex(), 0);
  ASSERT_EQ(geometry.GetVertex(1).GetHalfedge().GetSourceVertex().GetIndex(), 1);
  ASSERT_EQ(geometry.GetVertex(2).GetHalfedge().GetSourceVertex().GetIndex(), 2);
  ASSERT_EQ(geometry.GetVertex(3).GetHalfedge().GetSourceVertex().GetIndex(), 3);
#if 0
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
#endif
}

TEST(GeometryTest, HexahedronGeometryExplicit) {
  auto hexahedron = Polyhedron::MakeHexahedron();

  Geometry geometry(hexahedron.GetFaces());

  auto halfedges = geometry.GetHalfedges();

  Vertex v(&geometry, 6);

  for (auto adj : v.GetAdjacentVertices()) {
    std::println("{}", adj.GetIndex());
  }

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(0)), HalfedgeInformation(0, 0, 1, 0, 22));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(1)), HalfedgeInformation(1, 0, 2, 1, 7));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(2)), HalfedgeInformation(2, 0, 3, 2, 16));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(3)), HalfedgeInformation(3, 0, 0, 3, 13));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(4)), HalfedgeInformation(1, 1, 5, 4, 21));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(5)), HalfedgeInformation(5, 1, 6, 5, 11));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(6)), HalfedgeInformation(6, 1, 7, 6, 17));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(7)), HalfedgeInformation(2, 1, 4, 1, 1));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(8)), HalfedgeInformation(5, 2, 9, 7, 20));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(9)), HalfedgeInformation(4, 2, 10, 8, 15));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(10)), HalfedgeInformation(7, 2, 11, 9, 18));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(11)), HalfedgeInformation(6, 2, 8, 5, 5));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(12)), HalfedgeInformation(4, 3, 13, 10, 23));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(13)), HalfedgeInformation(0, 3, 14, 3, 3));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(14)), HalfedgeInformation(3, 3, 15, 11, 19));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(15)), HalfedgeInformation(7, 3, 12, 8, 9));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(16)), HalfedgeInformation(3, 4, 17, 2, 2));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(17)), HalfedgeInformation(2, 4, 18, 6, 6));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(18)), HalfedgeInformation(6, 4, 19, 9, 10));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(19)), HalfedgeInformation(7, 4, 16, 11, 14));

  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(20)), HalfedgeInformation(4, 5, 21, 7, 8));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(21)), HalfedgeInformation(5, 5, 22, 4, 4));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(22)), HalfedgeInformation(1, 5, 23, 0, 0));
  ASSERT_EQ(MakeHalfedge(geometry.GetHalfedge(23)), HalfedgeInformation(0, 5, 20, 10, 12));

#if 0
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
#endif
}

TEST(GeometryTest, WeirdFaces) {
  std::vector<FaceIndices> faces{{0, 1, 2}, {0, 1, 3}, {0, 1, 4}};

  Geometry geometry(faces);
}