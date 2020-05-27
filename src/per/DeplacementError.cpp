#include "per/DeplacementError.hpp"

namespace per
{
    DeplacementError::DeplacementError(const std::string& message) : std::runtime_error(message) {}

    DeplacementError::~DeplacementError() {}
} // namespace donjon