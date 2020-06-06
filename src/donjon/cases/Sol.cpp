#include "donjon/cases/Sol.hpp"
#include <iostream>
#include "donjon/cases/ICaseVisiteur.hpp"
#include "err/DepotErreur.hpp"
#include "err/SansObjetErreur.hpp"

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
            notifier(*this);
        }
    }

    obj::IObjet_S Sol::ramasser()
    {
        // On récupère l'objet et on vide la case.
        getObjet();
        obj::IObjet_S objet = m_objet;
        m_objet = obj::IObjet_S();
        notifier(*this);
        return objet;
    }

    bool Sol::aObjet() const { return m_objet != nullptr; }

    const obj::IObjet_SC Sol::getObjet() const
    {
        // On s'assure qu'il y ait un objet à récupérer.
        if (m_objet == nullptr) { throw err::SansObjetErreur("Il n'y a rien à ramasser"); }
        else
        {
            return m_objet;
        }
    }

    const obj::IObjet_S Sol::getObjet()
    {
        // On s'assure qu'il y ait un objet à récupérer.
        if (m_objet == nullptr) { throw err::SansObjetErreur("Il n'y a rien à ramasser"); }
        else
        {
            return m_objet;
        }
    }

    void Sol::enEntree(per::APersonnage& personnage)
    {
        if (m_objet != nullptr)
        {
            try
            {
                // Ajoute l'objet au personnage et le retire de la case.
                personnage.ajouterObjet(m_objet);
                m_objet = obj::IObjet_S();
                notifier(*this);
            }
            catch (const std::logic_error& ex)
            {
                // Le personnage ne supporte pas l'ajout d'objet.
            }
        }
        // Ne rien faire.
    }

    bool Sol::estPraticable() const { return true; }

    void Sol::enActivation(per::APersonnage&)
    {
        // Ne rien faire.
    }

    bool Sol::estTransparent() const { return true; }

    void Sol::accepter(ICaseVisiteur& visiteur) const { visiteur.visite(*this); }

    void Sol::actualiser()
    {
        if (aObjet()) m_objet->actualiser();
    }
} // namespace donjon::cases
