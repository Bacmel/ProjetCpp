#ifndef __ROBLITE_HPP__
#define __ROBLITE_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include "controlleur/IControlleur.hpp"
#include "partie/Partie.hpp"
#include "vue/Fenetre.hpp"
#include "vue/PartieDessinable.hpp"

class Roblite
{
private:
    std::shared_ptr<partie::Partie> m_partie;
    std::shared_ptr<vue::Fenetre> m_fenetre;
    std::shared_ptr<vue::PartieDessinable> m_partieDessinable;
    controlleur::IControlleur_S m_controlleur;

public:
    Roblite();

    void jouer();

private:
    void preparerPartie();
};
#endif // __ROBLITE_HPP__
