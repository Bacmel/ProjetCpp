#include "per/Fantassin.hpp"
#include "err/DeplacementErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "per/IPersonnageVisiteur.hpp"

namespace per
{
    Fantassin::Fantassin() : APersonnage(1, hex::Coordonnees()) { m_arme = obj::IObjet_S(new obj::Taser()); }

    void Fantassin::deplacer(Deplacement deplacement, hex::Coordonnees cible)
    {
        switch (deplacement)
        {
        case Deplacement::Forcer:
            m_position = cible;
            break;
        case Deplacement::Marcher:
            if (m_position.distance(cible) != 1)
            { throw err::DeplacementErreur("Fantassin::deplacer : Hors de porter de marche"); }
            else
            {
                m_position = cible;
                notifier(*this);
            }
            break;
        default:
            throw err::DeplacementErreur("Fantassin::deplacer : Deplacement non precise");
        }
    }

    void Fantassin::accepter(IPersonnageVisiteur& visiteur) const { visiteur.visiter(*this); }

    void Fantassin::actualiser() {}

    obj::IObjet_SC Fantassin::getObjet(size_t indice) const
    {
        if (indice != 0) { throw std::out_of_range("APersonnage::getObjet : Opération non supportée (pas de sac)"); }
        return m_arme;
    }

    obj::IObjet_S Fantassin::getObjet(size_t indice)
    {
        if (indice != 0) { throw std::out_of_range("APersonnage::getObjet : Opération non supportée (pas de sac)"); }
        return m_arme;
    }
    size_t Fantassin::tailleSac() const { return 1; }

    hex::Masque Fantassin::getPorte() const
    {
        return hex::Masque::contour();
    }

} // namespace per
