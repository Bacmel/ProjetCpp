#include "donjon/cases/Trou.hpp"
#include "donjon/DepotError.hpp"
#include "donjon/SansObjetError.hpp"

namespace donjon::cases
{
    void Trou::deposer(obj::IObjet_S objet)
    {
        throw DepotError("Trou::deposer : Impossible de poser l'objet");
    }

    obj::IObjet_S Trou::ramasser() { throw SansObjetError("Trou::ramasser : Il n'y a pas d'objet"); }

    const obj::IObjet& Trou::getObjet() const
    {
        throw SansObjetError("Trou::getObjet : Il n'y a pas d'objet");
    }

    void Trou::enEntree(per::APersonnage& personnage)
    {
        // Tue le personnage.
        personnage.subitAttaque(999);
    }

    bool Trou::estPraticable() const { return false; }

    void Trou::enActivation(per::APersonnage& personnage)
    {
        // Ne rien faire
    }

    bool Trou::estTransparent() const { return true; }
} // namespace donjon::cases
