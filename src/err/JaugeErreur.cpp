#include "err/JaugeErreur.hpp"

namespace err
{
    JaugeErreur::JaugeErreur(const std::string& message) : std::runtime_error(message) {}
} // namespace err
