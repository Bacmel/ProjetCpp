#include "per/Heros.hpp"
#include <algorithm>
#include <cmath>
#include "err/DeplacementErreur.hpp"
#include "hex/Masque.hpp"
#include "per/IPersonnageVisiteur.hpp"

namespace per
{
    Heros::Heros(size_t pvMax) : APersonnage::APersonnage(pvMax, hex::Coordonnees()), m_sac() {}

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

    size_t Heros::tailleSac() const { return m_sac.size(); }

    void Heros::actualiser()
    {
        m_zoneEffet.clear();
        for (auto objet : m_sac)
        {
            objet->actualiser();
        }
    }

    hex::Masque Heros::getPorte() const { return hex::Masque::contour(); }

    hex::Masque Heros::getZoneDegat(hex::Coordonnees cible) const
    {
        hex::Masque voisin1 = hex::Masque::contour();
        hex::Masque voisin2 = hex::Masque::contour().deplacer(cible);
        return voisin1 && voisin2;
    }
}; // namespace per
