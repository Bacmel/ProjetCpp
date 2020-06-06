#ifndef __ITERATEURCARTEHEXAGONE_HPP__
#define __ITERATEURCARTEHEXAGONE_HPP__

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

    public:
        /**
         * @brief Crée un itérateur pour la carte hexagone donnée.
         *
         * @param carte La carte sur laquelle on veut itérer.
         */
        IterateurCarteHexagone(const CarteHexagone<T>* carte) :
            m_carte(carte),
            m_colonne(0),
            m_ligne(-1),
        {
            m_colonneMax = carte->getRayon() * 2;
        }

        bool aSuite() override { return m_colonne < m_colonneMax || m_ligne < (int)m_carte->getRayon(); }

        Coordonnees suite() override
        {
            if (m_colonne <= (int)m_carte->getRayon())
            {
                // La taille des lignes est croissante. (Partie gauche de l'hexagone)
                if (m_ligne < (int)m_carte->getRayon() + m_colonne) { m_ligne++; }
                else
                {
                    // On a fini la ligne, on démarre la colonne suivante.
                    m_colonne++;
                    m_ligne = 0;
                }
            }
            else
            {
                // La taille des lignes est décroissante. (Partie droite de l'hexagone)
                if (m_ligne < 3 * (int)m_carte->getRayon() - m_colonne) { m_ligne++; }
                else
                {
                    // On a fini la ligne, on démarre la colonne suivante.
                    m_colonne++;
                    m_ligne = 0;
                }
            }
            // Conversion des coordonnées "mémoire" en axiale.
            int r = m_ligne - std::min(m_colonne, (int)m_carte->getRayon());
            int q = m_colonne - m_carte->getRayon();
            Coordonnees c(r, q);
            return c;
        }
    };
} // namespace hex

#endif // __ITERATEURCARTEHEXAGONE_HPP__
