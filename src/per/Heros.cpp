#include "per/Heros.hpp"
#include <algorithm>
#include <cmath>
#include "IPersonnageVisiteur.hpp"

namespace per
{
    Heros::Heros(size_t pvMax) : APersonnage::APersonnage(pvMax, hex::Coordonnees()), m_sac() {}

    void Heros::addObjet(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_sac.push_back(objet); }
    }

    void Heros::rmObjet(obj::IObjet_S objet)
    {
        m_sac.erase(std::remove(m_sac.begin(), m_sac.end(), objet), m_sac.end());
    }

    void Heros::addSanteMax(int sante)
    {
        if (sante < 0 and m_pvMax <= (size_t)abs(sante)) // Degats
        {
            m_pvMax = 0;
            m_pv = 0;
        }
        else
        {
            m_pvMax += sante;
            if (sante < 0 and m_pv <= (size_t)abs(sante)) // Degats
            { m_pv = 0; }
            else
            {
                m_pv += sante;
            }
        }
    }

    void Heros::accepter(IPersonnageVisiteur& visiteur) { visiteur.visiter(*this); }
}; // namespace per
