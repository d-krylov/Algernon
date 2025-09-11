#include "algernon/common/algernon.h"
#include "gtest/gtest.h"
#include <print>

using namespace Algernon;

TEST(GeometryTest, TetrahedronGeometry) {

#if 0
  auto tetrahedron = Polyhedron::MakeTetrahedron();

  Geometry geometry(tetrahedron.GetFaces());

  auto halfedges = geometry.GetHalfedges();

  for (auto h : halfedges) {
    std::println("{} {}", h.face_, h.vertex_);
  }

  ASSERT_EQ(halfedges[0].face_, 0);
  ASSERT_EQ(halfedges[1].face_, 0);
  ASSERT_EQ(halfedges[2].face_, 0);
  ASSERT_EQ(halfedges[3].face_, 1);
  ASSERT_EQ(halfedges[4].face_, 1);
  ASSERT_EQ(halfedges[5].face_, 1);
  ASSERT_EQ(halfedges[6].face_, 2);
  ASSERT_EQ(halfedges[7].face_, 2);
  ASSERT_EQ(halfedges[8].face_, 2);
  ASSERT_EQ(halfedges[9].face_, 3);
  ASSERT_EQ(halfedges[10].face_, 3);
  ASSERT_EQ(halfedges[11].face_, 3);

#endif
}