#ifndef ALGERNON_CONWAY_H
#define ALGERNON_CONWAY_H

#include "algernon/mesh/shapes/include/polyhedron.h"

namespace Algernon {

Polyhedron OperatorKIS(const Polyhedron &polyhedron);
Polyhedron OperatorDUAL(const Polyhedron &polyhedron);
Polyhedron OperatorExpand(const Polyhedron &polyhedron, float alpha);

} // namespace Algernon

#endif // ALGERNON_CONWAY_H