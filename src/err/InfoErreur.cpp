#include "err/InfoErreur.hpp"

namespace err
{
    InfoErreur::InfoErreur(const std::string& message) : std::runtime_error(message) {}
} // namespace err
