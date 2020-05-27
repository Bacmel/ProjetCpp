#include "per/Heros.hpp"
#include "err/DeplacementError.hpp"
#include <algorithm>
#include <cmath>

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

    void Heros::deplacer(Deplacement deplacement, hex::Coordonnees cible)
    {
        switch(deplacement)
        {
            case Deplacement::Forcer:
                m_position = cible;
                break;
            case Deplacement::Marcher:
                if(m_position.distance(cible)!=1)
                {
                    throw err::DeplacementError("Heros::deplacer : Hors de porter de marche");
                }
                else
                {
                    m_position = cible;
                }
                break;
            case Deplacement::Sauter:
                if(m_position.distance(cible)!=2)
                {
                    throw err::DeplacementError("Heros::deplacer : Hors de porter de saut");
                }
                else
                {
                    m_position = cible;
                }
                break; 
        }
    }
}; // namespace per
