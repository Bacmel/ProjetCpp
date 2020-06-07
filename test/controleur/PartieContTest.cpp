#include "controleur/PartieCont.hpp"
#include "catch.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "vue/Fenetre.hpp"

using namespace controleur;

TEST_CASE("Creation et utilisation de PartieCont", "[PartieCont]")
{
    // Generation de la partie.
    partie::strat::IStrategie_S stratHumain = std::make_shared<partie::strat::JoueurHumain>();
    std::shared_ptr<partie::Partie> partie = std::make_shared<partie::Partie>(stratHumain);
    // Gereration de la partie dessinable.
    sf::VideoMode vm = sf::VideoMode(500, 500);
    std::shared_ptr<vue::Fenetre> fenetre = std::make_shared<vue::Fenetre>(vm, "Test");
    std::shared_ptr<vue::PartieDessinable> dessinable = std::make_shared<vue::PartieDessinable>(25);
    dessinable->setElement(*partie);
    fenetre->setDessinable(dessinable);
    PartieCont partieCont(*dessinable, *partie);
    sf::Event event;
    REQUIRE_NOTHROW(partieCont.enEvenement(*fenetre, event));
}