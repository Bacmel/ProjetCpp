#include "obj/Taser.hpp"
#include <map>
#include "donjon/IDonjon.hpp"
#include "obj/IObjetVisiteur.hpp"

namespace obj
{
    Taser::Taser() : m_degat(1) {}

    bool Taser::estUtilisable() const { return true; }

    void Taser::utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& origine, const hex::Coordonnees& cible)
    {
        if (origine.distance(cible) == 1)
        {
            std::map<hex::Coordonnees, size_t> zoneEffet;
            zoneEffet[cible] = m_degat;
            donjon.degat(zoneEffet);
        }
    }

    void Taser::accepter(IObjetVisiteur& visiteur) const { visiteur.visiter(*this); }

    void Taser::actualiser() {}

    hex::Masque Taser::getPorte() const
    {
        return hex::Masque::contour();
    }

} // namespace obj
