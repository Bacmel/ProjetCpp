#include "per/APersonnage.hpp"

namespace per
{
    size_t APersonnage::idSuivante = 0;

    APersonnage::APersonnage(size_t pvMax, hex::Coordonnees position) :
        m_pvMax(pvMax),
        m_pv(pvMax),
        m_position(position),
        m_id(idSuivante)
    {
        idSuivante++;
    }

    APersonnage::~APersonnage() {}

    bool APersonnage::estVivant() const { return m_pv > 0; }

    void APersonnage::subitAttaque(size_t degat)
    {
        if (degat < m_pv) { m_pv -= degat; }
        else
        {
            m_pv = 0;
        }
    }
} // namespace per
