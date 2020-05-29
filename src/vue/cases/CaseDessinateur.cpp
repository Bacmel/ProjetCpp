#include "vue/cases/CaseDessinateur.hpp"
#include <SFML/Graphics.hpp>
#include "vue/TextureGest.hpp"

using namespace sf;

namespace vue::cases
{
    CaseDessinateur::CaseDessinateur(sf::RenderTarget& cible) :
        ADessinateur(50),
        m_textureSol(),
        m_textureTrou(),
        m_cible(cible),
        m_hexagone()
    {
        TextureGest& gest = TextureGest::getInstance();
        m_textureSol = gest.obtenir("resources/textures/cases/sol.png");
        m_textureTrou = gest.obtenir("resources/textures/cases/trou.png");
    }

    void CaseDessinateur::dessine(const hex::Coordonnees& position, donjon::cases::ICase& iCase)
    {
        Vector2u dim = m_cible.getSize();
        float rayon = getRayon();
        Vector2f pixel = hexVersPixel(position);
        m_hexagone = CircleShape(rayon, 6);
        m_hexagone.setOrigin(rayon, rayon);
        m_hexagone.setPosition(dim.x / 2 + pixel.x, dim.y / 2 + pixel.y);
        m_hexagone.setRotation(90);
        m_hexagone.setOutlineThickness(1);
        m_hexagone.setOutlineColor(Color::Black);
        iCase.accepter(*this);
        m_cible.draw(m_hexagone);
    }

    void CaseDessinateur::visite(__attribute__((unused)) const donjon::cases::Sol& sol)
    {
        m_hexagone.setTexture(m_textureSol.get());
    }

    void CaseDessinateur::visite(__attribute__((unused)) const donjon::cases::Trou& trou)
    {
        m_hexagone.setTexture(m_textureTrou.get());
    }
} // namespace vue::cases
