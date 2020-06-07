#include "per/APersonnage.hpp"
#include <stdexcept>
#include "err/DeplacementErreur.hpp"
#include "err/JaugeErreur.hpp"

namespace per
{
    size_t APersonnage::idSuivante = 0;

    APersonnage::APersonnage(size_t pvMax, hex::Coordonnees position) :
        m_pv(pvMax),
        m_position(position),
        m_id(idSuivante),
        m_zoneEffet()
    {
        idSuivante++;
    }

    bool APersonnage::estVivant() const { return m_pv.getVal() > 0; }

    void APersonnage::subirAttaque(size_t degat)
    {
        // Essaie de retirer la santé, en échec, on met la santé à 0.
        try
        {
            m_pv.ajouterValeur(-degat);
        }
        catch (const err::JaugeErreur&)
        {
            m_pv.vider();
        }
    }

    void APersonnage::ajouterSante(int sante)
    {
        // Essaie d'ajouter la santé, en échec, on met la santé à 0.
        try
        {
            m_pv.ajouterValeur(sante);
        }
        catch (const err::JaugeErreur&)
        {
            m_pv.vider();
        }
    }

    void APersonnage::ajouterSanteMax(int sante)
    {
        // Essaie d'ajouter la santé max, en échec, on met la santé et la santé
        // max à 0.
        try
        {
            m_pv.ajouterValeurMax(sante);
        }
        catch (const err::JaugeErreur&)
        {
            m_pv.ajouterValeurMax(-m_pv.getValMax());
            m_pv.vider();
        }
    }

    void APersonnage::tuer()
    {
        m_pv.vider();
    }

    void APersonnage::deplacer(Deplacement deplacement, hex::Coordonnees cible)
    {
        /* Calcul du masque de dégât. */
        hex::Masque masqueDegat = getZoneDegat(cible - m_position).deplacer(m_position);
        for (auto itr = masqueDegat.begin(); itr != masqueDegat.end(); itr++)
        {
            m_zoneEffet[*itr] += 1;
        }
        /* Gestion du deplacement .*/
        switch (deplacement)
        {
        case Deplacement::Forcer:
            m_position = cible;
            m_zoneEffet.clear();
            break;
        case Deplacement::Marcher:
            if (m_position.distance(cible) != 1)
            {
                m_zoneEffet.clear();
                throw err::DeplacementErreur("APersonnage::deplacer : Hors de porter de marche");
            }
            else
            {
                m_position = cible;
            }
            break;
        case Deplacement::Sauter:
            if (m_position.distance(cible) != 2)
            {
                m_zoneEffet.clear();
                throw err::DeplacementErreur("APersonnage::deplacer : Hors de porter de marche");
            }
            else
            {
                m_position = cible;
            }
            break;
        default:
            m_zoneEffet.clear();
            throw err::DeplacementErreur("APersonnage::deplacer : Deplacement non precise");
        }
    }

    void APersonnage::ajouterObjet(obj::IObjet_S)
    {
        throw std::logic_error("APersonnage::ajouterObjet : Operation non supportee.");
    }

    void APersonnage::retirerObjet(obj::IObjet_S)
    {
        throw std::logic_error("APersonnage::retirerObjet : Operation non supportee.");
    }

    size_t APersonnage::tailleSac() const { return 0; }

    obj::IObjet_SC APersonnage::getObjet(size_t) const
    {
        throw std::out_of_range("APersonnage::getObjet : Operation non supportee (pas de sac)");
    }

    obj::IObjet_S APersonnage::getObjet(size_t)
    {
        throw std::out_of_range("APersonnage::getObjet : Operation non supportee (pas de sac)");
    }
} // namespace per
