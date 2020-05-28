#include "vue/cases/CaseDessinateur.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "err/TextureESErreur.hpp"

using namespace sf;

namespace vue::cases
{
    CaseDessinateur::CaseDessinateur(sf::RenderTarget& cible) : m_textureSol(), m_cible(cible), m_rayon(50)
    {
        std::string chemin = "resources/textures/cases/sol.png";
        if (!m_textureSol.loadFromFile(chemin))
        { throw err::TextureESErreur("CaseDessinateur::CaseDessinateur : sol.png n'a pas pu être chargée.", chemin); }
        chemin = "resources/textures/cases/trou.png";
        if (!m_textureTrou.loadFromFile(chemin))
        {
            throw err::TextureESErreur("CaseDessinateur::CaseDessinateur : trou.png n'a pas pu être chargée.", chemin);
        }
    }

    void CaseDessinateur::dessine(const hex::Coordonnees& position, donjon::cases::ICase& iCase)
    {
        Vector2u dim = m_cible.getSize();
        m_hexagone = CircleShape(m_rayon, 6);
        float x = m_rayon / 2 * 3 * (float)position.getColonne();
        float y = m_rayon * sqrtf(3) * ((float)position.getColonne() / 2 + position.getLigne());
        m_hexagone.setOrigin(m_rayon, m_rayon);
        m_hexagone.setPosition(dim.x / 2 + x, dim.y / 2 + y);
        m_hexagone.setRotation(90);
        m_hexagone.setOutlineThickness(2);
        m_hexagone.setOutlineColor(Color::Black);
        iCase.accepter(*this);
        m_cible.draw(m_hexagone);
    }

    void CaseDessinateur::visite(__attribute__((unused)) const donjon::cases::Sol& sol)
    {
        m_hexagone.setTexture(&m_textureSol);
    }

    void CaseDessinateur::visite(__attribute__((unused)) const donjon::cases::Trou& trou)
    {
        m_hexagone.setTexture(&m_textureTrou);
    }
} // namespace vue::cases
