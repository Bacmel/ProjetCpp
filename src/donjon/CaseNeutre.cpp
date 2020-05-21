#include "donjon/CaseNeutre.hpp"
#include "donjon/DepotError.hpp"
#include "donjon/SansObjetError.hpp"

namespace donjon
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
} // namespace donjon
