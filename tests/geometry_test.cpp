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
  auto vertices = geometry.GetVertices();
  auto edges = geometry.GetEdges();
  auto faces = geometry.GetFaces();

  ASSERT_EQ(MakeHalfedge(halfedges[0]), HalfedgeInformation(0, 0, 1, 0, 11));
  ASSERT_EQ(MakeHalfedge(halfedges[1]), HalfedgeInformation(1, 0, 2, 1, 5));
  ASSERT_EQ(MakeHalfedge(halfedges[2]), HalfedgeInformation(2, 0, 0, 2, 7));

  ASSERT_EQ(MakeHalfedge(halfedges[3]), HalfedgeInformation(1, 1, 4, 3, 10));
  ASSERT_EQ(MakeHalfedge(halfedges[4]), HalfedgeInformation(3, 1, 5, 4, 8));
  ASSERT_EQ(MakeHalfedge(halfedges[5]), HalfedgeInformation(2, 1, 3, 1, 1));

  ASSERT_EQ(MakeHalfedge(halfedges[6]), HalfedgeInformation(3, 2, 7, 5, 9));
  ASSERT_EQ(MakeHalfedge(halfedges[7]), HalfedgeInformation(0, 2, 8, 2, 2));
  ASSERT_EQ(MakeHalfedge(halfedges[8]), HalfedgeInformation(2, 2, 6, 4, 4));

  ASSERT_EQ(MakeHalfedge(halfedges[9]), HalfedgeInformation(0, 3, 10, 5, 6));
  ASSERT_EQ(MakeHalfedge(halfedges[10]), HalfedgeInformation(3, 3, 11, 3, 3));
  ASSERT_EQ(MakeHalfedge(halfedges[11]), HalfedgeInformation(1, 3, 9, 0, 0));

  ASSERT_EQ(geometry.GetVertex(0).GetHalfedge().GetSourceVertex().GetIndex(), 0);
  ASSERT_EQ(geometry.GetVertex(1).GetHalfedge().GetSourceVertex().GetIndex(), 1);
  ASSERT_EQ(geometry.GetVertex(2).GetHalfedge().GetSourceVertex().GetIndex(), 2);
  ASSERT_EQ(geometry.GetVertex(3).GetHalfedge().GetSourceVertex().GetIndex(), 3);

  ASSERT_EQ(halfedges[faces[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[faces[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[faces[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[faces[3].GetIndex()].GetIndex(), 3);

  ASSERT_EQ(halfedges[edges[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[edges[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[edges[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[edges[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[edges[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[edges[5].GetIndex()].GetIndex(), 5);
}

TEST(GeometryTest, HexahedronGeometryExplicit) {
  auto hexahedron = Polyhedron::MakeHexahedron();

  Geometry geometry(hexahedron.GetFaces());

  auto halfedges = geometry.GetHalfedges();
  auto vertices = geometry.GetVertices();
  auto edges = geometry.GetEdges();
  auto faces = geometry.GetFaces();

  ASSERT_EQ(MakeHalfedge(halfedges[0]), HalfedgeInformation(0, 0, 1, 0, 22));
  ASSERT_EQ(MakeHalfedge(halfedges[1]), HalfedgeInformation(1, 0, 2, 1, 7));
  ASSERT_EQ(MakeHalfedge(halfedges[2]), HalfedgeInformation(2, 0, 3, 2, 16));
  ASSERT_EQ(MakeHalfedge(halfedges[3]), HalfedgeInformation(3, 0, 0, 3, 13));

  ASSERT_EQ(MakeHalfedge(halfedges[4]), HalfedgeInformation(1, 1, 5, 4, 21));
  ASSERT_EQ(MakeHalfedge(halfedges[5]), HalfedgeInformation(5, 1, 6, 5, 11));
  ASSERT_EQ(MakeHalfedge(halfedges[6]), HalfedgeInformation(6, 1, 7, 6, 17));
  ASSERT_EQ(MakeHalfedge(halfedges[7]), HalfedgeInformation(2, 1, 4, 1, 1));

  ASSERT_EQ(MakeHalfedge(halfedges[8]), HalfedgeInformation(5, 2, 9, 7, 20));
  ASSERT_EQ(MakeHalfedge(halfedges[9]), HalfedgeInformation(4, 2, 10, 8, 15));
  ASSERT_EQ(MakeHalfedge(halfedges[10]), HalfedgeInformation(7, 2, 11, 9, 18));
  ASSERT_EQ(MakeHalfedge(halfedges[11]), HalfedgeInformation(6, 2, 8, 5, 5));

  ASSERT_EQ(MakeHalfedge(halfedges[12]), HalfedgeInformation(4, 3, 13, 10, 23));
  ASSERT_EQ(MakeHalfedge(halfedges[13]), HalfedgeInformation(0, 3, 14, 3, 3));
  ASSERT_EQ(MakeHalfedge(halfedges[14]), HalfedgeInformation(3, 3, 15, 11, 19));
  ASSERT_EQ(MakeHalfedge(halfedges[15]), HalfedgeInformation(7, 3, 12, 8, 9));

  ASSERT_EQ(MakeHalfedge(halfedges[16]), HalfedgeInformation(3, 4, 17, 2, 2));
  ASSERT_EQ(MakeHalfedge(halfedges[17]), HalfedgeInformation(2, 4, 18, 6, 6));
  ASSERT_EQ(MakeHalfedge(halfedges[18]), HalfedgeInformation(6, 4, 19, 9, 10));
  ASSERT_EQ(MakeHalfedge(halfedges[19]), HalfedgeInformation(7, 4, 16, 11, 14));

  ASSERT_EQ(MakeHalfedge(halfedges[20]), HalfedgeInformation(4, 5, 21, 7, 8));
  ASSERT_EQ(MakeHalfedge(halfedges[21]), HalfedgeInformation(5, 5, 22, 4, 4));
  ASSERT_EQ(MakeHalfedge(halfedges[22]), HalfedgeInformation(1, 5, 23, 0, 0));
  ASSERT_EQ(MakeHalfedge(halfedges[23]), HalfedgeInformation(0, 5, 20, 10, 12));

  ASSERT_EQ(halfedges[vertices[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[vertices[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[vertices[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[vertices[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[vertices[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[vertices[5].GetIndex()].GetIndex(), 5);
  ASSERT_EQ(halfedges[vertices[6].GetIndex()].GetIndex(), 6);
  ASSERT_EQ(halfedges[vertices[7].GetIndex()].GetIndex(), 7);

  ASSERT_EQ(halfedges[faces[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[faces[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[faces[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[faces[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[faces[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[faces[5].GetIndex()].GetIndex(), 5);

  ASSERT_EQ(halfedges[edges[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[edges[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[edges[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[edges[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[edges[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[edges[5].GetIndex()].GetIndex(), 5);
  ASSERT_EQ(halfedges[edges[6].GetIndex()].GetIndex(), 6);
  ASSERT_EQ(halfedges[edges[7].GetIndex()].GetIndex(), 7);
}

TEST(GeometryTest, HexahedronGeometryImplicit) {
  auto hexahedron = Polyhedron::MakeHexahedron();

  Geometry geometry(hexahedron.GetFaces(), true);
  auto halfedges = geometry.GetHalfedges();
  auto vertices = geometry.GetVertices();
  auto edges = geometry.GetEdges();
  auto faces = geometry.GetFaces();

  ASSERT_EQ(MakeHalfedge(halfedges[0]), HalfedgeInformation(0, 0, 2, 0, 1));
  ASSERT_EQ(MakeHalfedge(halfedges[1]), HalfedgeInformation(1, 5, 21, 0, 0));
  ASSERT_EQ(MakeHalfedge(halfedges[2]), HalfedgeInformation(1, 0, 4, 1, 3));
  ASSERT_EQ(MakeHalfedge(halfedges[3]), HalfedgeInformation(2, 1, 8, 1, 2));
  ASSERT_EQ(MakeHalfedge(halfedges[4]), HalfedgeInformation(2, 0, 6, 2, 5));
  ASSERT_EQ(MakeHalfedge(halfedges[5]), HalfedgeInformation(3, 4, 13, 2, 4));
  ASSERT_EQ(MakeHalfedge(halfedges[6]), HalfedgeInformation(3, 0, 0, 3, 7));
  ASSERT_EQ(MakeHalfedge(halfedges[7]), HalfedgeInformation(0, 3, 22, 3, 6));

  ASSERT_EQ(MakeHalfedge(halfedges[8]), HalfedgeInformation(1, 1, 10, 4, 9));
  ASSERT_EQ(MakeHalfedge(halfedges[9]), HalfedgeInformation(5, 5, 1, 4, 8));
  ASSERT_EQ(MakeHalfedge(halfedges[10]), HalfedgeInformation(5, 1, 12, 5, 11));
  ASSERT_EQ(MakeHalfedge(halfedges[11]), HalfedgeInformation(6, 2, 14, 5, 10));
  ASSERT_EQ(MakeHalfedge(halfedges[12]), HalfedgeInformation(6, 1, 3, 6, 13));
  ASSERT_EQ(MakeHalfedge(halfedges[13]), HalfedgeInformation(2, 4, 19, 6, 12));

  ASSERT_EQ(MakeHalfedge(halfedges[14]), HalfedgeInformation(5, 2, 16, 7, 15));
  ASSERT_EQ(MakeHalfedge(halfedges[15]), HalfedgeInformation(4, 5, 9, 7, 14));
  ASSERT_EQ(MakeHalfedge(halfedges[16]), HalfedgeInformation(4, 2, 18, 8, 17));
  ASSERT_EQ(MakeHalfedge(halfedges[17]), HalfedgeInformation(7, 3, 20, 8, 16));
  ASSERT_EQ(MakeHalfedge(halfedges[18]), HalfedgeInformation(7, 2, 11, 9, 19));
  ASSERT_EQ(MakeHalfedge(halfedges[19]), HalfedgeInformation(6, 4, 23, 9, 18));

  ASSERT_EQ(MakeHalfedge(halfedges[20]), HalfedgeInformation(4, 3, 7, 10, 21));
  ASSERT_EQ(MakeHalfedge(halfedges[21]), HalfedgeInformation(0, 5, 15, 10, 20));

  ASSERT_EQ(MakeHalfedge(halfedges[22]), HalfedgeInformation(3, 3, 17, 11, 23));
  ASSERT_EQ(MakeHalfedge(halfedges[23]), HalfedgeInformation(7, 4, 5, 11, 22));

  ASSERT_EQ(halfedges[vertices[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[vertices[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[vertices[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[vertices[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[vertices[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[vertices[5].GetIndex()].GetIndex(), 5);
  ASSERT_EQ(halfedges[vertices[6].GetIndex()].GetIndex(), 6);
  ASSERT_EQ(halfedges[vertices[7].GetIndex()].GetIndex(), 7);

  ASSERT_EQ(halfedges[faces[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[faces[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[faces[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[faces[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[faces[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[faces[5].GetIndex()].GetIndex(), 5);

  ASSERT_EQ(halfedges[edges[0].GetIndex()].GetIndex(), 0);
  ASSERT_EQ(halfedges[edges[1].GetIndex()].GetIndex(), 1);
  ASSERT_EQ(halfedges[edges[2].GetIndex()].GetIndex(), 2);
  ASSERT_EQ(halfedges[edges[3].GetIndex()].GetIndex(), 3);
  ASSERT_EQ(halfedges[edges[4].GetIndex()].GetIndex(), 4);
  ASSERT_EQ(halfedges[edges[5].GetIndex()].GetIndex(), 5);
  ASSERT_EQ(halfedges[edges[6].GetIndex()].GetIndex(), 6);
  ASSERT_EQ(halfedges[edges[7].GetIndex()].GetIndex(), 7);
}

TEST(GeometryTest, HexahedronWithBoundary) {
  std::vector<FaceIndices> faces{
    {0, 1, 2, 3}, // FRONT
    {1, 5, 6, 2}, // RIGHT
    {5, 4, 7, 6}, // BACK
    {4, 0, 3, 7}  // LEFT
  };

  Geometry geometry(faces, true);
}

TEST(GeometryTest, SimpleMutation) {
  std::vector<FaceIndices> faces{{0, 1, 2, 3}};

  Geometry geometry(faces, true);

  geometry.InsertVertexInFace(geometry.GetFace(0));

  auto halfedges = geometry.GetHalfedges();

  ASSERT_EQ(MakeHalfedge(halfedges[0]), HalfedgeInformation(0, 0, 1, 0, 1));
}

TEST(GeometryTest, WeirdFaces) {
  std::vector<FaceIndices> faces{{0, 1, 2}, {0, 1, 3}, {0, 1, 4}};

  Geometry geometry(faces);
}