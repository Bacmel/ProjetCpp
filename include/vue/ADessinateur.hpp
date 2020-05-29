#ifndef __ADESSINATEUR_H__
#define __ADESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include "hex/Coordonnees.hpp"

namespace vue
{
    class ADessinateur
    {
    private:
        float m_rayon;

    public:
        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param rayon Le rayon du cercle circonscrit à l'hexagone (en pixels).
         */
        ADessinateur(float rayon);
        virtual ~ADessinateur() = 0;

        /**
         * @brief Obtient le rayon du cercle circonscrit à l'hexagone.
         *
         * @return Le rayon du cercle circonscrit à l'hexagone (en pixels).
         *
         * @see getCote()
         */
        inline float getRayon() const { return m_rayon; }

        /**
         * @brief Défini le rayon du cercle circonscrit à l'hexagone.
         *
         * @param rayon Le rayon du cercle circonscrit à l'hexagone (en pixels).
         *
         * @see setCote()
         */
        inline void setRayon(size_t rayon) { m_rayon = rayon; }

        /**
         * @brief Converti la position en pixel en une coordonnees hexagonale.
         *
         * @param pixel La position en pixel.
         * @return L'équivalent en grille hexagonale.
         */
        hex::Coordonnees pixelVersHex(const sf::Vector2u& pixel);

        /**
         * @brief Converti la coordonnees hexagonale en position en pixel.
         *
         * @param pixel La position en grille hexagonale.
         * @return L'équivalent en matrice de pixels.
         */
        sf::Vector2f hexVersPixel(const hex::Coordonnees& hex);
    };
} // namespace vue
#endif // __ADESSINATEUR_H__
