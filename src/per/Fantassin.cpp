#include "per/Fantassin.hpp"
#include "err/DeplacementErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "per/IPersonnageVisiteur.hpp"

namespace per
{
    Fantassin::Fantassin() : APersonnage(1, hex::Coordonnees()) { m_arme = obj::IObjet_S(new obj::Taser()); }

    void Fantassin::accepter(IPersonnageVisiteur& visiteur) const { visiteur.visiter(*this); }

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

    void Fantassin::actualiser()
    {
        m_zoneEffet.clear();
        m_arme->actualiser();
    }

    hex::Masque Fantassin::getPorte() const { return hex::Masque::contour(); }

    hex::Masque Fantassin::getZoneDegat(const hex::Coordonnees&) const { return hex::Masque(); }

} // namespace per
