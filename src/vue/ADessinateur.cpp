#include "vue/ADessinateur.hpp"
#include <cmath>

namespace vue
{
    ADessinateur::ADessinateur(float rayon) : m_rayon(0) { setRayon(rayon); }

    ADessinateur::~ADessinateur() {}

    float ADessinateur::getCote() const { return m_rayon * 2. / 3.; }

    void ADessinateur::setCote(float cote) { m_rayon = cote * 3. / 2.; }

    hex::Coordonnees ADessinateur::pixelVersHex(const sf::Vector2u& pixel)
    {
        float q = pixel.x / m_rayon * 2. / 3.;
        float r = (sqrtf(3) * pixel.y - pixel.x) / 3.;
        hex::Coordonnees hex;
        hex.arrondir(r, q);
        return hex;
    }

    sf::Vector2f ADessinateur::hexVersPixel(const hex::Coordonnees& hex)
    {
        sf::Vector2f pixel;
        pixel.x = m_rayon * (float)hex.getColonne() * 3. / 2.;
        pixel.y = m_rayon * (hex.getColonne() / 2. + hex.getLigne()) * sqrtf(3);
        return pixel;
    }
} // namespace vue
