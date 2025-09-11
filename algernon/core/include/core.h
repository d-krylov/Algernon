#ifndef ALGERNON_CORE_H
#define ALGERNON_CORE_H

#include <source_location>
#include <string_view>

namespace Algernon {

void CORE_ASSERT(bool status, std::string_view message, std::source_location location);

} // namespace Algernon

#endif // ALGERNON_CORE_H