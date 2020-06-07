#include "donjon/cases/Sol.hpp"
#include <memory>
#include "catch.hpp"
#include "obj/GravityGun.hpp"
#include "per/Heros.hpp"

using namespace donjon::cases;
using namespace obj;
using namespace per;

TEST_CASE("Creation et manipulation de Sol", "[Sol]")
{
    Sol sol;
    Heros heros(3);

    REQUIRE(sol.estPraticable());
    REQUIRE(sol.estTransparent());

    SECTION("Sol::enActivation")
    {
        // Sauvegarde de l'état du héros.
        size_t sante = heros.getSante();
        size_t santeMax = heros.getSanteMax();
        hex::Coordonnees pos = heros.getPosition();
        bool vie = heros.estVivant();

        sol.enActivation(heros);
        // Pas d'influence sur le héros.
        REQUIRE(heros.getSante() == sante);
        REQUIRE(heros.getSanteMax() == santeMax);
        REQUIRE(heros.getPosition() == pos);
        REQUIRE(heros.estVivant() == vie);
    }

    SECTION("Sol::enEntree")
    {
        Heros heros(3);
        // Sauvegarde de l'état du héros.
        size_t sante = heros.getSante();
        size_t santeMax = heros.getSanteMax();
        hex::Coordonnees pos = heros.getPosition();
        bool vie = heros.estVivant();

        sol.enEntree(heros);
        // Pas d'influence sur le héros.
        REQUIRE(heros.getSante() == sante);
        REQUIRE(heros.getSanteMax() == santeMax);
        REQUIRE(heros.getPosition() == pos);
        REQUIRE(heros.estVivant() == vie);

        IObjet_S objet = std::make_shared<GravityGun>();
        sol.deposer(objet);
        sol.enEntree(heros);
        REQUIRE_THROWS(sol.getObjet());
        REQUIRE_NOTHROW(heros.getObjet(0));
    }

    SECTION("Sol::deposer")
    {
        IObjet_S objet = std::make_shared<GravityGun>();
        // Dépot d'un objet null.
        REQUIRE_THROWS(sol.deposer(IObjet_S()));
        // Dépot d'un objet sur une case vide.
        REQUIRE_NOTHROW(sol.deposer(objet));
        REQUIRE(sol.aObjet());
        REQUIRE(sol.getObjet() == objet);
        // Dépot d'un objet sur une case pleine.
        REQUIRE_THROWS(sol.deposer(std::make_shared<GravityGun>()));
    }

    SECTION("Sol::ramaser")
    {
        // Ramasser sur une case vide.
        REQUIRE_THROWS(sol.ramasser());
        // Ramasser sur une case pleine.
        IObjet_S objet = std::make_shared<GravityGun>();
        sol.deposer(objet);
        IObjet_S objObtenu;
        REQUIRE(sol.aObjet());
        REQUIRE_NOTHROW(objObtenu = sol.ramasser());
        REQUIRE_FALSE(sol.aObjet());
        REQUIRE(objObtenu == objet);
        // S'assure que la case est à nouveau vide.
        REQUIRE_THROWS(sol.ramasser());
    }
}
