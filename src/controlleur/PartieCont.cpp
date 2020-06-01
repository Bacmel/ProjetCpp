#include "controlleur/PartieCont.hpp"
#include <iostream>
#include <stdexcept>
#include "vue/Fenetre.hpp"

using namespace sf;
using namespace partie;
using namespace utils;

namespace controlleur
{
    PartieCont::PartieCont(const vue::PartieDessinable& dessinable, Partie& partie) :
        m_dessinable(&dessinable),
        m_partie(&partie),
        m_convertisseur()
    {
        if (dessinable.getElement() != &partie)
        { throw std::invalid_argument("PartieCont::PartieCont : Le dessinable ne dessine pas la partie"); }
    }

    PartieCont::~PartieCont() {}

    void PartieCont::enEvenement(const vue::Fenetre& source, sf::Event& even)
    {
        if (even.type != Event::EventType::MouseButtonPressed) { return; }
        Vector2i clickPos(even.mouseButton.x, even.mouseButton.y);
        std::cout << "Click at : " << clickPos.x << ", " << clickPos.y << std::endl;
        const sf::RenderWindow& rw = source.getRenderWindow();
        Vector2f coordWindow = rw.mapPixelToCoords(clickPos);
        auto dim = rw.getSize();
        clickPos.x = coordWindow.x - dim.x / 2;
        clickPos.y = coordWindow.y - dim.y / 2;
        std::cout << "Click at : " << clickPos.x << ", " << clickPos.y << std::endl;
        hex::Coordonnees pos = m_convertisseur(m_dessinable->getCote(), clickPos);
        std::cout << "Pos: " << pos << std::endl;

        m_partie->demande(pos);
    }
} // namespace controlleur
