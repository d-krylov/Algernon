#ifndef ALGERNON_SDF_H
#define ALGERNON_SDF_H

#include "algernon/mathematics/include/mathematics_types.h"
#include <span>

namespace Algernon {

float SDSphere(Vector3f p, float radius);
float SDBox(Vector3f p, float x_size, float y_size, float z_size);
float SDBoxFrame(Vector3f p, float x_size, float y_size, float z_size, float e);
float SDRoundBox(Vector3f p, float x_size, float y_size, float z_size, float radius);
float SDTorus(Vector3f p, float r1, float r2);
float SDVerticalCapsule(Vector3f p, float h, float r);
float SDRoundedCylinder(Vector3f p, float r1, float r2, float h);

float OperationIntersection(float d1, float d2);
float OperationUnion(std::span<const float> distances);

Vector3f OperationTwist(Vector3f p, float k);

} // namespace Algernon

#endif // ALGERNON_SDF_H