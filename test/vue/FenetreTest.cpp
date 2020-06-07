#include "vue/Fenetre.hpp"
#include "catch.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "vue/PartieDessinable.hpp"
#include "controleur/PartieCont.hpp"

using namespace vue;

TEST_CASE("Construction et manipulation de Fenetre", "[Fenetre]")
{
    sf::VideoMode vm = sf::VideoMode(500, 500);
    std::shared_ptr<vue::Fenetre> fenetre = std::make_shared<vue::Fenetre>(vm, "Test");

    SECTION("Fenetre:getRenderWindow") { REQUIRE_NOTHROW(fenetre->getRenderWindow()); }

    SECTION("Fenetre::actualiser") { REQUIRE_NOTHROW(fenetre->actualiser()); }

    SECTION("Fenetre::actualiserUneFois") { REQUIRE_NOTHROW(fenetre->actualiserUneFois()); }

    SECTION("Fenetre::attacher")
    {
        partie::strat::IStrategie_S stratHumain = std::make_shared<partie::strat::JoueurHumain>();
        std::shared_ptr<partie::Partie> partie = std::make_shared<partie::Partie>(stratHumain);
        std::shared_ptr<PartieDessinable> dessinable = std::make_shared<PartieDessinable>(25);
        dessinable->setElement(partie);
        fenetre->setDessinable(dessinable);
        controleur::IControleur_S partieCont = std::make_shared<controleur::PartieCont>(dessinable, partie);
        sf::Event::EventType event;
        REQUIRE_NOTHROW(fenetre->attacher(event, partieCont));
    }

    SECTION("Fenetre::detacher")
    {
        partie::strat::IStrategie_S stratHumain = std::make_shared<partie::strat::JoueurHumain>();
        std::shared_ptr<partie::Partie> partie = std::make_shared<partie::Partie>(stratHumain);
        std::shared_ptr<PartieDessinable> dessinable = std::make_shared<PartieDessinable>(25);
        dessinable->setElement(partie);
        fenetre->setDessinable(dessinable);
        controleur::IControleur_S partieCont = std::make_shared<controleur::PartieCont>(dessinable, partie);
        sf::Event::EventType event;
        REQUIRE_NOTHROW(fenetre->detacher(event, partieCont));
    }

    SECTION("Fenetre::setDessinable")
    {
        partie::strat::IStrategie_S stratHumain = std::make_shared<partie::strat::JoueurHumain>();
        std::shared_ptr<partie::Partie> partie = std::make_shared<partie::Partie>(stratHumain);
        std::shared_ptr<PartieDessinable> dessinable = std::make_shared<PartieDessinable>(25);
        dessinable->setElement(partie);
        REQUIRE_NOTHROW(fenetre->setDessinable(dessinable));
    }
}
