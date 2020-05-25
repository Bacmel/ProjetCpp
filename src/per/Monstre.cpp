#include "per/Monstre.hpp"
#include <stdexcept>

namespace per
{
    Monstre::Monstre(size_t pvMax, hex::Coordonnees coor, obj::IObjet_S arme) :
        APersonnage(pvMax, hex::Coordonnees()),
        m_arme(arme)
    {
        if (m_arme == nullptr) { throw std::invalid_argument("Monstre::Monstre : Arme est un pointeur null"); }
    }
} // namespace per
