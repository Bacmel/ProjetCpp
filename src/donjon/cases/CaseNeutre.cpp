#include "donjon/cases/CaseNeutre.hpp"
#include "donjon/DepotError.hpp"
#include "donjon/SansObjetError.hpp"

namespace donjon::cases
{
    CaseNeutre::CaseNeutre() : m_objet() {}

    void CaseNeutre::deposer(obj::IObjet_S objet)
    {
        if (objet != nullptr) { m_objet = objet; }
        else
        {
            throw DepotError("Un objet est déjà présent");
        }
    }

    obj::IObjet_S CaseNeutre::ramasser()
    {
        getObjet();
        obj::IObjet_S objet = m_objet;
        m_objet = obj::IObjet_S();
        return objet;
    }

    const obj::IObjet& CaseNeutre::getObjet() const
    {
        if (m_objet != nullptr) { return *m_objet; }
        else
        {
            throw SansObjetError("Il n'y a rien à ramasser");
        }
    }

    void CaseNeutre::enEntree(per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool CaseNeutre::estPraticable() const { return true; }

    void CaseNeutre::enActivation(per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool CaseNeutre::estTransparent() const { return true; }
} // namespace donjon::cases
