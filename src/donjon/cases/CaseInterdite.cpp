#include "donjon/cases/CaseInterdite.hpp"
#include "donjon/DepotError.hpp"
#include "donjon/SansObjetError.hpp"

namespace donjon::cases
{
    void CaseInterdite::deposer(obj::IObjet_S objet)
    {
        throw DepotError("CaseInterdite::deposer : Impossible de poser l'objet");
    }

    obj::IObjet_S CaseInterdite::ramasser() { throw SansObjetError("CaseInterdite::ramasser : Il n'y a pas d'objet"); }

    const obj::IObjet& CaseInterdite::getObjet() const
    {
        throw SansObjetError("CaseInterdite::getObjet : Il n'y a pas d'objet");
    }

    void CaseInterdite::enEntree(per::APersonnage& personnage)
    {
        // Tue le personnage.
        personnage.subitAttaque(999);
    }

    bool CaseInterdite::estPraticable() const { return false; }

    void CaseInterdite::enActivation(per::APersonnage& personnage)
    {
        // Ne rien faire
    }

    bool CaseInterdite::estTransparent() const { return true; }
} // namespace donjon::cases
