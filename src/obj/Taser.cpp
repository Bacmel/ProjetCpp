#include "obj/Taser.hpp"
#include "obj/IObjetVisiteur.hpp"
#include "donjon/IDonjon.hpp"
#include <map>

namespace obj
{
    Taser::Taser() : m_degat(1) {}

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
} // namespace obj