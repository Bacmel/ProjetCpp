#include "err/DeplacementErreur.hpp"

namespace err
{
    DeplacementErreur::DeplacementErreur(const std::string& message) : std::runtime_error(message) {}
} // namespace err
