#include "err/CreationErreur.hpp"

namespace err
{
    CreationErreur::CreationErreur(const std::string& message) : std::runtime_error(message) {}

    CreationErreur::~CreationErreur() {}
} // namespace err