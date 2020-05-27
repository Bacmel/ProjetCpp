#ifndef __ITERATEURCARTEHEXAGONE_H__
#define __ITERATEURCARTEHEXAGONE_H__

#include "hex/IIterateur.hpp"

namespace hex
{
    template <typename T>
    class CarteHexagone;

    template <typename T>
    class IterateurCarteHexagone : public IIterateur<Coordonnees>
    {
        const CarteHexagone<T>* m_carte;
        int m_ligne;
        int m_colonne;
        int m_ligneMax;
        Coordonnees m_centre;

    public:
        IterateurCarteHexagone(const CarteHexagone<T>* carte) :
            m_carte(carte),
            m_ligne(0),
            m_colonne(-1),
            m_centre(carte->getRayon(), carte->getRayon())
        {
            m_ligneMax = carte->getRayon() * 2;
        }

        bool aSuite() { return m_ligne < m_ligneMax || m_colonne < (int)m_carte->getRayon(); }

        Coordonnees suite()
        {
            if (m_ligne <= (int)m_carte->getRayon())
            {
                if (m_colonne < (int)m_carte->getRayon() + m_ligne) { m_colonne++; }
                else
                {
                    m_ligne++;
                    m_colonne = 0;
                }
            }
            else
            {
                if (m_colonne < 3 * (int)m_carte->getRayon() - m_ligne) { m_colonne++; }
                else
                {
                    m_ligne++;
                    m_colonne = 0;
                }
            }

            Coordonnees c(m_ligne, m_colonne);
            c = c - m_centre;
            return c;
        }
    };
} // namespace hex

#endif // __ITERATEURCARTEHEXAGONE_H__
