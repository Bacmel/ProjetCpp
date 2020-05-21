#include "per/Hero.hpp"
#include <algorithm>
#include <cmath>

namespace per
{
    Hero::Hero(size_t pvMax) : APersonnage::APersonnage(pvMax, hex::Coordonnees()), m_sac() {}

    void Hero::addObjet(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_sac.push_back(objet); }
    }

    void Hero::rmObjet(obj::IObjet_S objet)
    {
        m_sac.erase(std::remove(m_sac.begin(), m_sac.end(), objet), m_sac.end());
    }

    void Hero::addSanteMax(int sante)
    {
        if (sante < 0 and m_pvMax <= abs(sante)) // Degats
        {
            m_pvMax = 0;
            m_pv = 0;
        }
        else
        {
            m_pvMax += sante;
            if (sante < 0 and m_pv <= abs(sante)) // Degats
            { m_pv = 0; }
            else
            {
                m_pv += sante;
            }
        }
    }
}; // namespace per
