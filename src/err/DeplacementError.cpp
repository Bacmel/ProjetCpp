#include "err/DeplacementError.hpp"

namespace err
{
    DeplacementError::DeplacementError(const std::string& message) : std::runtime_error(message) {}

    DeplacementError::~DeplacementError() {}
} // namespace err