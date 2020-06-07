#ifndef __ROBLITE_HPP__
#define __ROBLITE_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include "controleur/IControleur.hpp"
#include "partie/Partie.hpp"
#include "vue/Fenetre.hpp"
#include "vue/PartieDessinable.hpp"

class Roblite
{
private:
    std::shared_ptr<partie::Partie> m_partie;
    std::shared_ptr<vue::Fenetre> m_fenetre;
    std::shared_ptr<vue::PartieDessinable> m_partieDessinable;
    controleur::IControleur_S m_controleur;

public:
    /**
     * @brief Construit un une instance du jeu.
     */
    Roblite();

    /**
     * @brief Lance la partie.
     *
     * La méthode ne retourne qu'une fois la fenêtre fermée.
     */
    void jouer();

private:
    /**
     * @brief Prépare le modèle.
     *
     * Crée une partie avec 2 équipes et 2 personnages par équipe ainsi que des
     * objets au sol.
     */
    void preparerPartie();
};
#endif // __ROBLITE_HPP__
