#include "controlleur/PartieCont.hpp"
#include <iostream>

using namespace sf;
using namespace utils;

namespace controlleur
{
    PartieCont::PartieCont(const vue::PartieDessinable& dessinable) :
        m_dessinable(&dessinable),
        m_convertisseur()
    {
    }

    PartieCont::~PartieCont() {}

    void PartieCont::enEvenement(sf::Event& even)
    {
        if (even.type != Event::EventType::MouseButtonPressed) { return; }
        Vector2i clickPos(even.mouseButton.x, even.mouseButton.y);
        std::cout << "Click at : " << clickPos.x << ", " << clickPos.y << std::endl;
        clickPos.x -= 250;
        clickPos.y -= 250;
        std::cout << "Click at : " << clickPos.x << ", " << clickPos.y << std::endl;
        hex::Coordonnees pos = m_convertisseur(m_dessinable->getCote(), clickPos);
        std::cout << "Pos: " << pos << std::endl;
    }
} // namespace controlleur
