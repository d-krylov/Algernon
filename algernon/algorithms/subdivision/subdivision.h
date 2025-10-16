#ifndef ALGERNON_SUBDIVISION_H
#define ALGERNON_SUBDIVISION_H

#include "algernon/mesh/include/mesh.h"

namespace Algernon {

Mesh CatmullClark(std::span<const Vector3f> vertices, std::span<const FaceIndices> facets);

} // namespace Algernon

#endif // ALGERNON_SUBDIVISION_H