#include "Roblite.hpp"
#include "controleur/PartieCont.hpp"
#include "obj/GravityGun.hpp"
#include "obj/Taser.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "per/Fantassin.hpp"
#include "per/Heros.hpp"

Roblite::Roblite() : m_partie(), m_fenetre(), m_partieDessinable(), m_controleur()
{
    preparerPartie();
    // Prépare la vue.
    sf::VideoMode vm = sf::VideoMode(500, 500);
    m_fenetre = std::make_shared<vue::Fenetre>(vm, "Roblite");
    sf::RenderWindow& window = m_fenetre->getRenderWindow();
    window.setFramerateLimit(60);
    m_partieDessinable = std::make_shared<vue::PartieDessinable>(25);
    m_partieDessinable->setElement(m_partie);
    m_fenetre->setDessinable(m_partieDessinable);
    // Prépare le controleur.
    m_controleur = std::make_shared<controleur::PartieCont>(*m_partieDessinable, *m_partie);
    m_fenetre->attacher(sf::Event::MouseButtonPressed, m_controleur);
}

void Roblite::jouer()
{
    // Execute la machine à état pour démarrer la partie et entre dans la boucle
    // principale du programme.
    m_partie->demander();
    m_fenetre->actualiser();
}

void Roblite::preparerPartie()
{
    partie::strat::IStrategie_S stratHumain = std::make_shared<partie::strat::JoueurHumain>();
    m_partie = std::make_shared<partie::Partie>(stratHumain);
    // Crée l'équipe 1.
    per::APersonnage_S heros = std::make_shared<per::Heros>(3);
    m_partie->genererPersonnage(heros, 0);
    per::APersonnage_S fantassin = std::make_shared<per::Fantassin>();
    m_partie->genererPersonnage(fantassin, 0);
    // Crée l'équipe 2.
    size_t eqp2 = m_partie->genererEquipe(stratHumain);
    per::APersonnage_S herosAdverse = std::make_shared<per::Heros>(3);
    m_partie->genererPersonnage(herosAdverse, eqp2);
    // Dépose des objets.
    obj::IObjet_S gravityGun = std::make_shared<obj::GravityGun>();
    m_partie->genererObjet(gravityGun);
    obj::IObjet_S taser = std::make_shared<obj::Taser>();
    m_partie->genererObjet(taser);
}
