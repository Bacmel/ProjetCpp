#include "utils/HexPixelConvertisseur.hpp"
#include <cmath>

namespace utils
{
    sf::Vector2f HexPixelConvertisseur::operator()(float cote, const hex::Coordonnees& hex) const
    {
        sf::Vector2f pixel;
        pixel.x = cote * (float)hex.getColonne() * 3. / 2.;
        pixel.y = cote * (hex.getColonne() / 2. + hex.getLigne()) * sqrtf(3);
        return pixel;
    }

    hex::Coordonnees HexPixelConvertisseur::operator()(float cote, const sf::Vector2i& pixel) const
    {
        float q = pixel.x / cote * 2. / 3.;
        float r = (sqrtf(3) * pixel.y - pixel.x) / 3. / cote;
        hex::Coordonnees hex = hex::Coordonnees::arrondir(r, q);
        return hex;
    }
} // namespace utils
