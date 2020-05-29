#include "donjon/cases/Sol.hpp"
#include <iostream>
#include "donjon/cases/ICaseVisiteur.hpp"
#include "err/DepotErreur.hpp"
#include "err/SansObjetErreur.hpp"
#include "donjon/cases/ICaseVisiteur.hpp"

namespace donjon::cases
{
    Sol::Sol() : m_objet() {}

    void Sol::deposer(obj::IObjet_S objet)
    {
        // On s'assure que l'objet existe et que la case est vide.
        if (objet == nullptr) { throw err::DepotErreur("Sol::deposer : L'objet est un pointeur null"); }
        if (m_objet != nullptr) { throw err::DepotErreur("Un objet est déjà présent"); }
        else
        {
            // On stock ce nouvel objet.
            m_objet = objet;
        }
    }

    obj::IObjet_S Sol::ramasser()
    {
        // On récupère l'objet et on vide la case.
        getObjet();
        obj::IObjet_S objet = m_objet;
        m_objet = obj::IObjet_S();
        return objet;
    }

    const obj::IObjet& Sol::getObjet() const
    {
        // On s'assure qu'il y ait un objet à récupérer.
        if (m_objet == nullptr) { throw err::SansObjetErreur("Il n'y a rien à ramasser"); }
        else
        {
            return *m_objet;
        }
    }

    // __attribute__((unused)) Signal au compilateur que l'argument n'est pas utilisé
    void Sol::enEntree(__attribute__((unused)) per::APersonnage& personnage)
    {
        if (m_objet != nullptr)
        {
            try
            {
                // Ajoute l'objet au personnage et le retire de la case.
                personnage.ajouterObjet(m_objet);
                m_objet = obj::IObjet_S();
            }
            catch (const std::logic_error& ex)
            {
                // Le personnage ne supporte pas l'ajout d'objet.
            }
        }
        // Ne rien faire.
    }

    bool Sol::estPraticable() const { return true; }

    void Sol::enActivation(__attribute__((unused)) per::APersonnage& personnage)
    {
        // Ne rien faire.
    }

    bool Sol::estTransparent() const { return true; }

    void Sol::accepter(ICaseVisiteur& visiteur) const { visiteur.visite(*this); }
} // namespace donjon::cases
