#include "algernon/mesh/include/triangle.h"

namespace Algernon {

float GetTriangleArea2D(float x1, float y1, float x2, float y2, float x3, float y3) {
  return (x1 - x2) * (y2 - y3) - (x2 - x3) * (y1 - y2);
}

Triangle::Triangle(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2) : p0_(p0), p1_(p1), p2_(p2) {
}

Vector3f Triangle::GetBarycentricUVW(const Vector3f &p) const {
  auto m = glm::cross(p1_ - p0_, p2_ - p0_);
  auto xyz = glm::abs(m);
  auto nominator_u = 0.0f;
  auto nominator_v = 0.0f;
  auto one_over_denominator = 0.0f;

  if (xyz.x >= xyz.y && xyz.x >= xyz.z) {
    nominator_u = GetTriangleArea2D(p.y, p.z, p1_.y, p1_.z, p2_.y, p2_.z);
    nominator_v = GetTriangleArea2D(p.y, p.z, p2_.y, p2_.z, p0_.y, p0_.z);
    one_over_denominator = 1.0f / m.x;
  } else if (xyz.y >= xyz.x && xyz.y >= xyz.z) {
    nominator_u = GetTriangleArea2D(p.x, p.z, p1_.x, p1_.z, p2_.x, p2_.z);
    nominator_v = GetTriangleArea2D(p.x, p.z, p2_.x, p2_.z, p0_.x, p0_.z);
    one_over_denominator = 1.0f / -m.y;
  } else {
    nominator_u = GetTriangleArea2D(p.x, p.y, p1_.x, p1_.y, p2_.x, p2_.y);
    nominator_v = GetTriangleArea2D(p.x, p.y, p2_.x, p2_.y, p0_.x, p0_.y);
    one_over_denominator = 1.0f / m.z;
  }

  auto u = nominator_u * one_over_denominator;
  auto v = nominator_v * one_over_denominator;

  return Vector3f(u, v, 1.0f - u - v);
}

Vector3f Triangle::GetCentroid() const {
  return (p0_ + p1_ + p2_) / 3.0f;
}

} // namespace Algernon