#include "err/SansObjetErreur.hpp"

namespace err
{
    SansObjetErreur::SansObjetErreur(const std::string& message) : std::runtime_error(message) {}
} // namespace err
