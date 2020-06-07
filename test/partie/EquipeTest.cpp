#include "partie/Equipe.hpp"
#include "catch.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "per/Fantassin.hpp"
#include "partie/Partie.hpp"
using namespace partie;

TEST_CASE("Creation et manipulation de Equipe", "[Equipe]")
{
    strat::IStrategie_S strat = std::make_shared<strat::JoueurHumain>();
    Equipe equipe(strat);
    per::APersonnage_S perso1 = std::make_shared<per::Fantassin>();
    per::APersonnage_S perso2 = std::make_shared<per::Fantassin>();
    REQUIRE(equipe.compterMembres() == 0);

    SECTION("Equipe::ajouterMembre")
    {
        REQUIRE_NOTHROW(equipe.ajouterMembre(perso1));
        REQUIRE_FALSE(equipe.estMembre(*perso2));
        REQUIRE(equipe.estMembre(perso1->getId()));
    }

    SECTION("Equipe::retirerMembre")
    {
        REQUIRE_NOTHROW(equipe.ajouterMembre(perso1));
        REQUIRE(equipe.estMembre(*perso1));
        REQUIRE_NOTHROW(equipe.retirerMembre(perso1));
        REQUIRE_FALSE(equipe.estMembre(*perso1));
    }

    SECTION("Equipe::getMembre")
    {
        REQUIRE_THROWS(equipe.getMembre(0));
        REQUIRE_NOTHROW(equipe.ajouterMembre(perso1));
        REQUIRE_THROWS(equipe.getMembre(1));
        REQUIRE_NOTHROW(equipe.getMembre(0));
        REQUIRE(equipe.getMembre(0)==perso1);
    }

    SECTION("Equipe::jouer")
    {
        equipe.ajouterMembre(perso1);
        Partie partie(strat);
        equipe.jouer(partie);
        REQUIRE(partie.getEquipes().at(0).compterMembres()==equipe.compterMembres());
    }

    SECTION("Equipe::retirerMort")
    {
        REQUIRE_NOTHROW(equipe.ajouterMembre(perso1));
        REQUIRE_NOTHROW(equipe.ajouterMembre(perso2));
        REQUIRE(equipe.compterMembres()==equipe.compterSurvivant());
        perso1->tuer();
        REQUIRE_FALSE(equipe.compterMembres()==equipe.compterSurvivant());
        equipe.retirerMorts();
        REQUIRE(equipe.compterMembres()==equipe.compterSurvivant());
        REQUIRE_FALSE(equipe.estMembre(*perso1));
        REQUIRE(equipe.estMembre(*perso2));
    }
}