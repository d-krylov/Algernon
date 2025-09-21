#ifndef ALGERNON_MATHEMATICS_TYPES_H
#define ALGERNON_MATHEMATICS_TYPES_H

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Algernon {

using Vector2f = glm::vec2;
using Vector3f = glm::vec3;
using Vector4f = glm::vec4;
using Vector2i = glm::ivec2;
using Vector3i = glm::ivec3;
using Vector4i = glm::ivec4;
using Vector2u = glm::uvec2;
using Vector3u = glm::uvec3;
using Vector4u = glm::uvec4;
using Vector2d = glm::dvec2;
using Vector3d = glm::dvec3;
using Vector4d = glm::dvec4;
using Matrix2f = glm::mat2x2;
using Matrix3f = glm::mat3x3;
using Matrix4f = glm::mat4x4;
using Quaternion = glm::quat;

inline constexpr auto PI_ = glm::pi<float>();

inline constexpr auto EPSILON = 0.0001f;

} // namespace Algernon

#endif // ALGERNON_MATHEMATICS_TYPES_H