#include "algernon/common/algernon.h"
#include "gtest/gtest.h"

using namespace Algernon;

TEST(MeshTest, FacaApi) {

  FaceIndices face{7, 3, 5, 1, 8, 2, 9, 6, 4};

  ASSERT_EQ(face.GetEdge(0), Index2(7, 3));
  ASSERT_EQ(face.GetEdge(1), Index2(3, 5));
  ASSERT_EQ(face.GetEdge(2), Index2(5, 1));
  ASSERT_EQ(face.GetEdge(3), Index2(1, 8));
  ASSERT_EQ(face.GetEdge(4), Index2(8, 2));
  ASSERT_EQ(face.GetEdge(5), Index2(2, 9));
  ASSERT_EQ(face.GetEdge(6), Index2(9, 6));
  ASSERT_EQ(face.GetEdge(7), Index2(6, 4));
  ASSERT_EQ(face.GetEdge(8), Index2(4, 7));
}

TEST(MeshTest, MeshTools) {

  std::vector<FaceIndices> faces{{0, 1, 2, 3, 4, 5}, {6, 7, 8, 9, 3, 2}};

  ASSERT_EQ(GetNumberEdgesInFacesSlow(faces), 11);

  auto icosahedron = Polyhedron::MakeIcosahedron();

  ASSERT_EQ(icosahedron.GetNumberOfVertices(), 12);
  ASSERT_EQ(icosahedron.GetNumberOfEdges(), 30);
  ASSERT_EQ(icosahedron.GetEulerСharacteristic(), 2);

  auto tetrahedron = Polyhedron::MakeTetrahedron();

  ASSERT_EQ(tetrahedron.GetEulerСharacteristic(), 2);

  auto edge_face = GetEdgeFaceMap(tetrahedron.GetFaces());

  ASSERT_EQ(edge_face[Index2(0, 1)], 0);
  ASSERT_EQ(edge_face[Index2(1, 2)], 0);
  ASSERT_EQ(edge_face[Index2(2, 0)], 0);

  ASSERT_EQ(edge_face[Index2(1, 3)], 1);
  ASSERT_EQ(edge_face[Index2(3, 2)], 1);
  ASSERT_EQ(edge_face[Index2(2, 1)], 1);

  ASSERT_EQ(edge_face[Index2(0, 2)], 2);
  ASSERT_EQ(edge_face[Index2(2, 3)], 2);
  ASSERT_EQ(edge_face[Index2(3, 0)], 2);

  ASSERT_EQ(edge_face[Index2(0, 3)], 3);
  ASSERT_EQ(edge_face[Index2(3, 1)], 3);
  ASSERT_EQ(edge_face[Index2(1, 0)], 3);
}