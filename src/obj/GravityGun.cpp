#include "obj/GravityGun.hpp"
#include <map>
#include <stdexcept>
#include "donjon/IDonjon.hpp"
#include "hex/IterateurCarteHexagone.hpp"
#include "obj/IObjetVisiteur.hpp"

using namespace hex;
using namespace std;

namespace obj
{
    GravityGun::GravityGun() : m_distance(1), m_aire(), m_charge(1)
    {
        // Pousse le personnage sur la case immédiatement en face.
        m_aire.insert(Coordonnees::direction(Direction::Nord));
    }

    GravityGun::GravityGun(size_t distance, Masque aire, size_t timeMax) :
        m_distance(distance),
        m_aire(aire),
        m_charge(timeMax)
    {
        // Pousse le personnage sur la case immédiatement en face.
        m_aire.insert(Coordonnees::direction(Direction::Nord));
    }

    bool GravityGun::estUtilisable() const { return m_charge.getVal() == m_charge.getValMax(); }

    void GravityGun::utiliser(donjon::IDonjon& donjon, const Coordonnees& origine, const Coordonnees& cible)
    {
        // Vérifie la charge du gravity gun.
        if (!estUtilisable()) { throw std::runtime_error("GravityGun::utiliser : L'objet n'est pas prêt."); }
        // Vérifie la porté.
        if (origine.distance(cible) != 1)
        { throw std::invalid_argument("GravityGun::utiliser : La cible n'est pas adajente à l'origine."); }
        // Construit l'Area of Effect du gravity gun (l'oriente vers la cible).
        Direction direction = origine.direction(cible);
        Masque aire = m_aire.tournerVers(Coordonnees(), direction, Direction::Nord);
        std::map<Coordonnees, Direction> aoe;
        for (auto itr = aire.begin(); itr != aire.end(); itr++)
        {
            Coordonnees pos = *itr + origine;
            aoe.insert(pair<Coordonnees, Direction>(pos, direction));
        }
        // Utilise l'objet et vide sa charge.
        donjon.pousse(aoe, m_distance);
        m_charge.vider();
    }

    void GravityGun::accepter(IObjetVisiteur& visiteur) const { visiteur.visiter(*this); }

    void GravityGun::actualiser() { m_charge.ajouterValeur(1); }

    hex::Masque GravityGun::getPorte() const { return hex::Masque::contour(); }

    hex::Masque GravityGun::getZoneDegat(const hex::Coordonnees& cible) const
    {
        Coordonnees origine;
        Direction direction = origine.direction(cible);
        // Oriente correctement le masque d'effet.
        return m_aire.tournerVers(Coordonnees(), direction, Direction::Nord);
    }

} // namespace obj
