#include "utils/Jauge.hpp"
#include "err/JaugeErreur.hpp"

namespace utils
{
    void Jauge::ajouterValeur(int valeur)
    {
        // On vérifie que la m_val de la jauge soit positive après addition de
        // valeur.
        if ((int)m_val < -valeur)
        { throw err::JaugeErreur("Jauge::ajouteValeur : m_val negatif"); }
        else if (m_val + valeur < m_valMax)
        {
            m_val += valeur;
        }
        else
        {
            // On sature la valeur.
            m_val = m_valMax;
        }
    }

    void Jauge::ajouterValeurMax(int valeur)
    {
        // On vérifie que la m_valMax de la jauge soit positive après addition
        // de valeur.
        if ((int)m_valMax < -valeur)
        { throw err::JaugeErreur("Jauge::ajouteValeurMax : m_valMax negatif"); }
        else
        {
            m_valMax += valeur;
            // Adapte la valeur pour garder la différence constante.
            ajouterValeur(valeur);
        }
    }

    void Jauge::remplir() { m_val = m_valMax; }

    void Jauge::vider() { m_val = 0; }

} // namespace utils
