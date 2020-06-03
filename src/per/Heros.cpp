#include "per/Heros.hpp"
#include <algorithm>
#include <cmath>
#include "err/DeplacementErreur.hpp"
#include "per/IPersonnageVisiteur.hpp"
#include "hex/Masque.hpp"

namespace per
{
    Heros::Heros(size_t pvMax) : APersonnage::APersonnage(pvMax, hex::Coordonnees()), m_sac() {}

    void Heros::deplacer(Deplacement deplacement, hex::Coordonnees cible)
    {
        hex::Masque voisin1 = hex::Masque::contour().deplacer(m_position);
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
                notifier(*this);
            }
            break;
        case Deplacement::Sauter:
            if (m_position.distance(cible) != 2)
            { throw err::DeplacementErreur("Heros::deplacer : Hors de porter de saut"); }
            else
            {
                m_position = cible;
                notifier(*this);
            }
            break;
        default:
            throw err::DeplacementErreur("Heros::deplacer : Deplacement non precise");
        }
        hex::Masque voisin2 = hex::Masque::contour().deplacer(m_position);
        hex::Masque voisinfinaux = voisin1&&voisin2;
        for(auto itr = voisinfinaux.begin(); itr != voisinfinaux.end(); itr++)
        {
            m_zoneEffet[*itr] += 1;
        }
        if(deplacement==Deplacement::Forcer)
        {
            m_zoneEffet.clear();
        }
    }

    void Heros::accepter(IPersonnageVisiteur& visiteur) const { visiteur.visiter(*this); }

    void Heros::ajouterObjet(obj::IObjet_S objet)
    {
        if (objet != nullptr)
        {
            m_sac.push_back(objet);
            notifier(*this);
        }
    }

    void Heros::retirerObjet(obj::IObjet_S objet)
    {
        m_sac.erase(std::remove(m_sac.begin(), m_sac.end(), objet), m_sac.end());
        notifier(*this);
    }

    size_t Heros::tailleSac() const { return m_sac.size(); }

    obj::IObjet_SC Heros::getObjet(size_t indice) const
    {
        obj::IObjet_S objet = m_sac.at(indice);
        return objet;
    }

    obj::IObjet_S Heros::getObjet(size_t indice)
    {
        obj::IObjet_S objet = m_sac.at(indice);
        return objet;
    }

    void Heros::actualiser()
    {
        m_zoneEffet.clear();
        for(auto objet : m_sac)
        {
            objet->actualiser();
        }
    }
    
    hex::Masque Heros::getPorte() const
    {
        return hex::Masque::contour();
    }
}; // namespace per
