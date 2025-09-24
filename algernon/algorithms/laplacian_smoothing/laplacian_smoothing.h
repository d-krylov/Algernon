#ifndef ALGERNON_LAPLACIAN_SMOOTHING_H
#define ALGERNON_LAPLACIAN_SMOOTHING_H

#include <span>
#include <vector>
#include "algernon/mathematics/include/mathematics_types.h"

namespace Algernon {

class FaceIndices;

std::vector<Vector3f> LaplacianSmoothing(std::span<const Vector3f> vertices, std::span<const FaceIndices> faces, uint32_t repetitions);

} // namespace Algernon

#endif // ALGERNON_LAPLACIAN_SMOOTHING_H
