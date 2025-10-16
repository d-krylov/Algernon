#ifndef ALGERNON_TRIANGULATION_H
#define ALGERNON_TRIANGULATION_H

#include "algernon/mesh/include/mesh.h"

namespace Algernon {

Mesh GetDelauney(std::span<const Vector3f> vertices, std::span<const FaceIndices> facets);

} // namespace Algernon

#endif // ALGERNON_TRIANGULATION_H