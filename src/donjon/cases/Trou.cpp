#include "donjon/cases/Trou.hpp"
#include "donjon/cases/ICaseVisiteur.hpp"
#include "err/DepotErreur.hpp"
#include "err/SansObjetErreur.hpp"

namespace donjon::cases
{
    Trou::Trou() {}

    void Trou::deposer(obj::IObjet_S) { throw err::DepotErreur("Trou::deposer : Impossible de poser l'objet"); }

    obj::IObjet_S Trou::ramasser() { throw err::SansObjetErreur("Trou::ramasser : Il n'y a pas d'objet"); }

    bool Trou::aObjet() const { return false; }

    const obj::IObjet& Trou::getObjet() const { throw err::SansObjetErreur("Trou::getObjet : Il n'y a pas d'objet"); }

    void Trou::enEntree(per::APersonnage& personnage)
    {
        // Tue le personnage.
        personnage.tuer();
    }

    bool Trou::estPraticable() const { return false; }

    void Trou::enActivation(per::APersonnage&)
    {
        // Ne rien faire
    }

    bool Trou::estTransparent() const { return true; }

    void Trou::accepter(ICaseVisiteur& visiteur) const { visiteur.visite(*this); }
} // namespace donjon::cases
