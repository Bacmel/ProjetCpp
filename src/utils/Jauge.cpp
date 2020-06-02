#include "utils/Jauge.hpp"
#include "err/JaugeErreur.hpp"

namespace utils
{
    void Jauge::ajouterValeur(int valeur)
    {
        if ((int)m_val < -valeur) // Throw
        { throw err::JaugeErreur("Jauge::ajouteValeur : m_val negatif"); }
        else if (m_val + valeur < m_valMax)
        {
            m_val += valeur;
        }
        else
        {
            m_val = m_valMax;
        }
    }

    void Jauge::ajouterValeurMax(int valeur)
    {
        if ((int)m_valMax < -valeur) // Throw
        { throw err::JaugeErreur("Jauge::ajouteValeurMax : m_valMax negatif"); }
        else
        {
            m_valMax += valeur;
            ajouterValeur(valeur);
        }
    }

    void Jauge::remplir() { m_val = m_valMax; }

    void Jauge::vider() { m_val = 0; }

} // namespace utils