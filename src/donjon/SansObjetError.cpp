#include "donjon/SansObjetError.hpp"

namespace donjon
{
    SansObjetError::SansObjetError(const std::string& message) : std::runtime_error(message) {}

    SansObjetError::~SansObjetError() {}
} // namespace donjon
