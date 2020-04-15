#include "donjon/DepotError.hpp"

namespace donjon
{
    DepotError::DepotError(const std::string& message) : std::runtime_error(message) {}

    DepotError::~DepotError() {}
} // namespace donjon
