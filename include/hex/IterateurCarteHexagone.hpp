#ifndef __ITERATEURCARTEHEXAGONE_H__
#define __ITERATEURCARTEHEXAGONE_H__

#include <cmath>
#include "hex/Coordonnees.hpp"
#include "hex/IIterateur.hpp"

namespace hex
{
    template <typename T>
    class CarteHexagone;

    template <typename T>
    class IterateurCarteHexagone : public IIterateur<Coordonnees>
    {
        const CarteHexagone<T>* m_carte;
        int m_colonne;
        int m_ligne;
        int m_colonneMax;
        Coordonnees m_centre;

    public:
        IterateurCarteHexagone(const CarteHexagone<T>* carte) :
            m_carte(carte),
            m_colonne(0),
            m_ligne(-1),
            m_centre(carte->getRayon(), carte->getRayon())
        {
            m_colonneMax = carte->getRayon() * 2;
        }

        bool aSuite() { return m_colonne < m_colonneMax || m_ligne < (int)m_carte->getRayon(); }

        Coordonnees suite()
        {
            if (m_colonne <= (int)m_carte->getRayon())
            {
                if (m_ligne < (int)m_carte->getRayon() + m_colonne) { m_ligne++; }
                else
                {
                    m_colonne++;
                    m_ligne = 0;
                }
            }
            else
            {
                if (m_ligne < 3 * (int)m_carte->getRayon() - m_colonne) { m_ligne++; }
                else
                {
                    m_colonne++;
                    m_ligne = 0;
                }
            }
            int r = m_ligne - std::min(m_colonne, (int) m_carte->getRayon());
            int q = m_colonne - m_carte->getRayon();
            Coordonnees c(r, q);
            return c;
        }
    };
} // namespace hex

#endif // __ITERATEURCARTEHEXAGONE_H__
