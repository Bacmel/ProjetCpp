#include "per/Heros.hpp"
#include <algorithm>
#include <cmath>
#include "err/DeplacementErreur.hpp"
#include "per/IPersonnageVisiteur.hpp"

namespace per
{
    Heros::Heros(size_t pvMax) : APersonnage::APersonnage(pvMax, hex::Coordonnees()), m_sac() {}

    void Heros::deplacer(Deplacement deplacement, hex::Coordonnees cible)
    {
        switch (deplacement)
        {
        case Deplacement::Forcer:
            m_position = cible;
            break;
        case Deplacement::Marcher:
            if (m_position.distance(cible) != 1)
            { throw err::DeplacementErreur("Heros::deplacer : Hors de porter de marche"); }
            else
            {
                m_position = cible;
            }
            break;
        case Deplacement::Sauter:
            if (m_position.distance(cible) != 2)
            { throw err::DeplacementErreur("Heros::deplacer : Hors de porter de saut"); }
            else
            {
                m_position = cible;
            }
            break;
        default:
            throw err::DeplacementErreur("Heros::deplacer : Deplacement non precise");
            break;
        }
    }

    void Heros::accepter(IPersonnageVisiteur& visiteur) const { visiteur.visiter(*this); }

    void Heros::ajouterObjet(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_sac.push_back(objet); }
    }

    void Heros::retirerObjet(obj::IObjet_S objet)
    {
        m_sac.erase(std::remove(m_sac.begin(), m_sac.end(), objet), m_sac.end());
    }

    size_t Heros::tailleSac() const { return m_sac.size(); }

    const obj::IObjet& Heros::getObjet(size_t indice)
    {
        obj::IObjet_S objet = m_sac.at(indice);
        return *objet;
    }
}; // namespace per
