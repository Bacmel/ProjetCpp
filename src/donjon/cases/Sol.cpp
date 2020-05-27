#include "donjon/cases/Sol.hpp"
#include "err/DepotErreur.hpp"
#include "err/SansObjetErreur.hpp"

namespace donjon::cases
{
    Sol::Sol() : m_objet() {}

    void Sol::deposer(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_objet = objet; }
        else
        {
            throw err::DepotErreur("Un objet est déjà présent");
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
            throw err::SansObjetErreur("Il n'y a rien à ramasser");
        }
    }

    // __attribute__((unused)) Signal au compilateur que l'argument n'est pas utilisé
    void Sol::enEntree(__attribute__((unused)) per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool Sol::estPraticable() const { return true; }

    void Sol::enActivation(__attribute__((unused)) per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool Sol::estTransparent() const { return true; }
} // namespace donjon::cases
