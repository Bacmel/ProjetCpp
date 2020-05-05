#include "donjon/Donjon.hpp"

namespace donjon
{
    Donjon::Donjon(const hex::ICarte_S<ICase_S>& carte) : m_entites(), m_carte(carte) {}

    void Donjon::deplace(const per::IPersonnage& personnage, const hex::Coordonnees& position)
    {
        try
        {
            ICase_S iCase = (*m_carte)(position);
        }
        catch (const std::out_of_range& ex)
        {
        }
    }
    Donjon::~Donjon() {}
} // namespace donjon
