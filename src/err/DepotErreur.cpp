#include "err/DepotErreur.hpp"

namespace err
{
    DepotErreur::DepotErreur(const std::string& message) : std::runtime_error(message) {}
} // namespace err
