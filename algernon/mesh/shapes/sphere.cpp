#include "algernon/mesh/shapes/include/sphere.h"

namespace Algernon {

std::vector<Vector3f> Sphere::GetVertices(uint32_t y_sectors, uint32_t xz_sectors) const {
  std::vector<Vector3f> out;

  auto xz_sector_step = 2 * PI_ / xz_sectors;
  auto y_sector_step = PI_ / y_sectors;

  for (auto y_sector = 0; y_sector <= y_sectors; y_sector++) {
    auto y_sector_angle = PI_ / 2 - y_sector * y_sector_step;

    auto xz = GetRadius() * std::cos(y_sector_angle);
    auto y = GetRadius() * std::sin(y_sector_angle);

    for (auto xz_sector = 0; xz_sector <= xz_sectors; xz_sector++) {
      auto xz_sector_angle = xz_sector * xz_sector_step;

      auto x = xz * std::cos(xz_sector_angle);
      auto z = xz * std::sin(xz_sector_angle);

      out.emplace_back(x, y, z);
    }
  }
  return out;
}

std::vector<Face> Sphere::GetFaces(int32_t y_sectors, int32_t xz_sectors) const {
  std::vector<Face> out;

  for (auto y_sector = 0; y_sector < y_sectors; y_sector++) {

    auto k1 = y_sector * (xz_sectors + 1);
    auto k2 = k1 + xz_sectors + 1;

    for (auto xz_sector = 0; xz_sector < xz_sectors; xz_sector++) {
      if (y_sector != 0) {
        out.emplace_back(k1, k2, k1 + 1);
      }

      if (y_sector != (y_sectors - 1)) {
        out.emplace_back(k1 + 1, k2, k2 + 1);
      }

      k1++;
      k2++;
    }
  }
  return out;
}

const Vector3f &Sphere::GetOrigin() const {
  return origin_;
}

float Sphere::GetRadius() const {
  return radius_;
}

Sphere::Sphere(const Vector3f &origin, float radius) : origin_(origin), radius_(radius) {
}

} // namespace Algernon