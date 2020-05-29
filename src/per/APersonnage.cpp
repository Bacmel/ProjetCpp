#include "per/APersonnage.hpp"
#include "err/JaugeErreur.hpp"
namespace per
{
    size_t APersonnage::idSuivante = 0;

    APersonnage::APersonnage(size_t pvMax, hex::Coordonnees position) :
        m_pv(pvMax),
        m_position(position),
        m_id(idSuivante)
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
        catch (err::JaugeErreur)
        {
            m_pv.vider();
        }
    }

    void APersonnage::ajouterSante(int sante)
    {
        try
        {
            m_pv.ajouterValeur(sante);
        }
        catch (err::JaugeErreur)
        {
            m_pv.vider();
        }
    }

    void APersonnage::ajouterSanteMax(int sante)
    {
        try
        {
            m_pv.ajouterValeurMax(sante);
        }
        catch (err::JaugeErreur)
        {
            m_pv.ajouterValeurMax(-m_pv.getValMax());
            m_pv.vider();
        }
    }

    void APersonnage::tuer() { m_pv.vider(); }
} // namespace per
