#ifndef __HEXPIXELCONVERTISSEUR_H__
#define __HEXPIXELCONVERTISSEUR_H__

#include <SFML/Graphics.hpp>
#include "hex/Coordonnees.hpp"

namespace utils
{
    class HexPixelConvertisseur
    {
    public:
        /**
         * @brief Converti la coordonnees hexagonale en position en pixel.
         *
         * @param cote La longueur du cote des hexagones.
         * @param pixel La position en grille hexagonale.
         * @return L'équivalent en matrice de pixels.
         */
        sf::Vector2f operator()(float cote, const hex::Coordonnees& hex) const;

        /**
         * @brief Converti la position en pixel en une coordonnees hexagonale.
         *
         * @param cote La longueur du cote des hexagones.
         * @param pixel La position en pixel.
         * @return L'équivalent en grille hexagonale.
         */
        hex::Coordonnees operator()(float cote, const sf::Vector2i& pixel) const;
    };
} // namespace utils
#endif // __HEXPIXELCONVERTISSEUR_H__
