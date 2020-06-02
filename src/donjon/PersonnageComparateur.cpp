#include "donjon/PersonnageComparateur.hpp"
#include <stdexcept>
namespace donjon
{
    bool PersonnageComparateur::operator()(const per::APersonnage_S& p1, const per::APersonnage_S& p2)
    {
        // On s'assure que les pointeur ne sont pas null.
        if (p1 == nullptr)
        { throw std::invalid_argument("PersonnageComparateur::operator() : p1 est un pointeur null."); }
        if (p2 == nullptr)
        { throw std::invalid_argument("PersonnageComparateur::operator() : p2 est un pointeur null."); }
        // On compare les identifiants.
        return p1->getId() < p2->getId();
    }
} // namespace donjon
