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

    void APersonnage::ajouteSante(int sante)
    {
        if (sante < 0 && m_pv <= (size_t)abs(sante)) // Degats
        { m_pv = 0; }
        else if (m_pv + sante < m_pvMax)
        {
            m_pv += sante;
        }
        else
        {
            m_pv = m_pvMax;
        }
    }

    void APersonnage::ajouteSanteMax(int sante)
    {
        if (sante < 0 && m_pvMax <= (size_t)abs(sante)) // Degats
        {
            m_pvMax = 0;
            m_pv = 0;
        }
        else
        {
            m_pvMax += sante;
            ajouteSante(sante);
        }
    }

    void APersonnage::tuer() { m_pv = 0; }
} // namespace per
