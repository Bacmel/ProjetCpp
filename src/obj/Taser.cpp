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
        /* Au CàC. */
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
        /* Masque indiquant toute les cases qu l'entoure. */
        return hex::Masque::contour();
    }

    hex::Masque Taser::getZoneDegat(const hex::Coordonnees& cible) const
    {
        hex::Masque degat;
        /* Au CàC. */
        if (cible.longueur() == 1) { degat = degat + cible; }
        else
        {
            throw std::invalid_argument("Taser::getZoneDegat : Cette cible n'est pas atteignable.");
        }

        return degat;
    }

} // namespace obj
