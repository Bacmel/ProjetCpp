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
        Vector2i clicPos(even.mouseButton.x, even.mouseButton.y);
        const sf::RenderWindow& rw = source.getRenderWindow();
        Vector2f coordonneesClic = rw.mapPixelToCoords(clicPos);
        // Clique sur l'inventaire.
        if (!clicObjet(coordonneesClic))
        {
            // Clique sur la carte.
            clicCase(coordonneesClic, source);
        }
    }

    bool PartieCont::clicObjet(const Vector2f& coordonneesClic)
    {
        try
        {
            per::APersonnage_SC personnage = m_partie->getPersoSelect();
            size_t nbObjet = personnage->tailleSac();
            for (size_t indice = 0; indice < nbObjet; indice++)
            {
                sf::FloatRect contours = m_dessinable->getCaseInventaire(indice);
                if (contours.contains(coordonneesClic))
                {
                    m_partie->demande(indice);
                    return true;
                }
            }
        }
        catch (...)
        {
        }
        return false;
    }

    void PartieCont::clicCase(const Vector2f& coordonneesClic, const vue::Fenetre& source)
    {
        const RenderWindow& rw = source.getRenderWindow();
        Vector2u dimension = rw.getSize();
        Vector2i coordCentree(coordonneesClic);
        coordCentree.x -= dimension.x / 2;
        coordCentree.y -= dimension.y / 2;
        hex::Coordonnees pos = m_convertisseur(m_dessinable->getCote(), coordCentree);
        m_partie->demande(pos);
    }
} // namespace controlleur
