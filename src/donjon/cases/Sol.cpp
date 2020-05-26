#include "donjon/cases/Sol.hpp"
#include "donjon/DepotError.hpp"
#include "donjon/SansObjetError.hpp"

namespace donjon::cases
{
    Sol::Sol() : m_objet() {}

    void Sol::deposer(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_objet = objet; }
        else
        {
            throw DepotError("Un objet est déjà présent");
        }
    }

    obj::IObjet_S Sol::ramasser()
    {
        getObjet();
        obj::IObjet_S objet = m_objet;
        m_objet = obj::IObjet_S();
        return objet;
    }

    const obj::IObjet& Sol::getObjet() const
    {
        if (m_objet != nullptr) { return *m_objet; }
        else
        {
            throw SansObjetError("Il n'y a rien à ramasser");
        }
    }

    void Sol::enEntree(per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool Sol::estPraticable() const { return true; }

    void Sol::enActivation(per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool Sol::estTransparent() const { return true; }
} // namespace donjon::cases
