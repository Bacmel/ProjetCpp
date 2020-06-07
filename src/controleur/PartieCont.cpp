#include "controleur/PartieCont.hpp"
#include <iostream>
#include <stdexcept>
#include "vue/Fenetre.hpp"

using namespace sf;
using namespace partie;
using namespace utils;

namespace controleur
{
    PartieCont::PartieCont(std::shared_ptr<const vue::PartieDessinable> dessinable,
                           std::shared_ptr<partie::Partie> partie) :
        m_dessinable(dessinable),
        m_partie(partie),
        m_convertisseur()
    {
        // Vérifie la validité des arguments.
        if (m_dessinable == nullptr) { throw std::invalid_argument("PartieCont::PartieCont : le dessinable est nul!"); }
        if (m_partie == nullptr) { throw std::invalid_argument("PartieCont::PartieCont : la partie est nulle !"); }
        if (m_dessinable->getElement().get() != m_partie.get())
        { throw std::invalid_argument("PartieCont::PartieCont : Le dessinable ne dessine pas la partie"); }
    }

    void PartieCont::enEvenement(const vue::Fenetre& source, sf::Event& even)
    {
        // S'assure que l'évênemt est un clique.
        if (even.type != Event::EventType::MouseButtonPressed) { return; }
        // Récupère la position du clique dans le repère "monde".
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
            // Identifie la case de l'inventaire cliquée.
            for (size_t indice = 0; indice < nbObjet; indice++)
            {
                sf::FloatRect contours = m_dessinable->getCaseInventaire(indice);
                if (contours.contains(coordonneesClic))
                {
                    // Transmet l'information à la MAE.
                    m_partie->demander(indice);
                    return true;
                }
            }
        }
        catch (const std::logic_error&)
        {
        }
        return false;
    }

    void PartieCont::clicCase(const Vector2f& coordonneesClic, const vue::Fenetre& source)
    {
        // Convertie les coordonnées du clic sur la fenêtre en position sur la
        // grille.
        const RenderWindow& rw = source.getRenderWindow();
        Vector2u dimension = rw.getSize();
        Vector2i coordCentree(coordonneesClic);
        coordCentree.x -= dimension.x / 2;
        coordCentree.y -= dimension.y / 2;
        hex::Coordonnees pos = m_convertisseur(m_dessinable->getCote(), coordCentree);
        // Transmet l'information à la MAE.
        try
        {
            m_partie->demander(pos);
        }
        catch (const std::logic_error&)
        {
        }
    }
} // namespace controleur
