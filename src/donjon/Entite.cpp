#include "donjon/Entite.hpp"
#include <stdexcept>

namespace donjon
{
    Entite::Entite(per::IPersonnage_S personnage) : m_id(idSuivante++), m_position(), m_personnage(personnage)
    {
        if (personnage == nullptr) {
            throw std::invalid_argument("Pointeur nul vers un personnage");
        }
    }

    bool Entite::operator<(const Entite& autre) const { return m_id < autre.m_id; }

    bool Entite::operator>(const Entite& autre) const { return m_id > autre.m_id; }

} // namespace donjon
