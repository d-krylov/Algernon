#include "SDF.h"
#include <algorithm>

namespace Algernon {

// https://iquilezles.org/articles/distfunctions/

float SDSphere(Vector3f p, float radius) {
  return glm::length(p) - radius;
}

float SDBox(Vector3f p, float x_size, float y_size, float z_size) {
  auto q = glm::abs(p) - Vector3f(x_size, y_size, z_size);
  return glm::length(glm::max(q, 0.0f)) + glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);
}

float SDBoxFrame(Vector3f p, float x_size, float y_size, float z_size, float e) {
  p = glm::abs(p) - Vector3f(x_size, y_size, z_size);
  auto q = abs(p + e) - e;
  auto a = glm::length(glm::max(Vector3f(p.x, q.y, q.z), 0.0f)) + glm::min(glm::max(p.x, glm::max(q.y, q.z)), 0.0f);
  auto b = glm::length(glm::max(Vector3f(q.x, p.y, q.z), 0.0f)) + glm::min(glm::max(q.x, glm::max(p.y, q.z)), 0.0f);
  auto c = glm::length(glm::max(Vector3f(q.x, q.y, p.z), 0.0f)) + glm::min(glm::max(q.x, glm::max(q.y, p.z)), 0.0f);
  return glm::min(glm::min(a, b), c);
}

float SDRoundBox(Vector3f p, float x_size, float y_size, float z_size, float radius) {
  auto q = glm::abs(p) - Vector3f(x_size, y_size, z_size) + radius;
  return glm::length(glm::max(q, 0.0f)) + glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f) - radius;
}

float SDTorus(Vector3f p, float r1, float r2) {
  auto q = Vector2f(glm::length(Vector2f(p.x, p.z)) - r1, p.y);
  return glm::length(q) - r2;
}

float SDVerticalCapsule(Vector3f p, float h, float r) {
  p.y -= glm::clamp(p.y, 0.0f, h);
  return glm::length(p) - r;
}

float SDRoundedCylinder(Vector3f p, float r1, float r2, float h) {
  auto d = Vector2f(glm::length(Vector2f(p.x, p.z)) - 2.0 * r1 + r2, glm::abs(p.y) - h);
  return glm::min(glm::max(d.x, d.y), 0.0f) + glm::length(glm::max(d, 0.0f)) - r2;
}

float OperationIntersection(float d1, float d2) {
  return glm::max(d1, d2);
}

float OperationUnion(std::span<const float> distances) {
  return std::ranges::min(distances);
}

Vector3f OperationTwist(Vector3f p, float k) {
  auto c = glm::cos(k * p.y);
  auto s = glm::sin(k * p.y);
  auto m = Matrix2f(c, -s, s, c);
  auto q = Vector3f(m * Vector2f(p.x, p.z), p.y);
  return q;
}

} // namespace Algernon