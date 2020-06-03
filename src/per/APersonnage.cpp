#include "per/APersonnage.hpp"
#include <stdexcept>
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

    APersonnage::~APersonnage() {}

    bool APersonnage::estVivant() const { return m_pv.getVal() > 0; }

    void APersonnage::subitAttaque(size_t degat)
    {
        try
        {
            m_pv.ajouterValeur(-degat);
        }
        catch (const err::JaugeErreur&)
        {
            m_pv.vider();
        }
        notifier(*this);
    }

    void APersonnage::ajouterSante(int sante)
    {
        try
        {
            m_pv.ajouterValeur(sante);
        }
        catch (const err::JaugeErreur&)
        {
            m_pv.vider();
        }
        notifier(*this);
    }

    void APersonnage::ajouterSanteMax(int sante)
    {
        try
        {
            m_pv.ajouterValeurMax(sante);
        }
        catch (const err::JaugeErreur&)
        {
            m_pv.ajouterValeurMax(-m_pv.getValMax());
            m_pv.vider();
        }
        notifier(*this);
    }

    void APersonnage::tuer()
    {
        m_pv.vider();
        notifier(*this);
    }

    void APersonnage::ajouterObjet(obj::IObjet_S)
    {
        throw std::logic_error("APersonnage::ajouterObjet : Opération non supportée.");
    }

    void APersonnage::retirerObjet(obj::IObjet_S)
    {
        throw std::logic_error("APersonnage::retirerObjet : Opération non supportée.");
    }

    size_t APersonnage::tailleSac() const { return 0; }

    obj::IObjet_SC APersonnage::getObjet(size_t) const
    {
        throw std::out_of_range("APersonnage::getObjet : Opération non supportée (pas de sac)");
    }

    obj::IObjet_S APersonnage::getObjet(size_t)
    {
        throw std::out_of_range("APersonnage::getObjet : Opération non supportée (pas de sac)");
    }
} // namespace per
