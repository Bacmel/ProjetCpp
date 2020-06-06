#include "obj/GravityGun.hpp"
#include <memory>
#include "catch.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/ACase.hpp"
#include "donjon/cases/Sol.hpp"
#include "hex/CarteHexagone.hpp"
#include "per/Heros.hpp"

using namespace obj;

TEST_CASE("Creation et manipulation de GravityGun", "[GravityGun]")
{
    IObjet_S gravitygun1 = std::make_shared<GravityGun>();
    hex::ICarte_S<donjon::cases::ACase_S> carte = std::make_shared<hex::CarteHexagone<donjon::cases::ACase_S> >(5);
    carte->remplir(std::make_shared<donjon::cases::Sol>());
    donjon::IDonjon_S donjon = std::make_shared<donjon::Donjon>(carte);
    hex::Coordonnees c1;
    hex::Coordonnees c2 = hex::Coordonnees::direction(hex::Direction::Sud);
    hex::Coordonnees c3 = hex::Coordonnees::direction(hex::Direction::Nord);
    per::APersonnage_S heros1 = std::make_shared<per::Heros>(3);

    SECTION("GravityGun::estUtilisable")
    {
        REQUIRE(gravitygun1->estUtilisable());
        REQUIRE_NOTHROW(gravitygun1->utiliser(*donjon, c2, c1));
        REQUIRE_FALSE(gravitygun1->estUtilisable());
    }

    SECTION("GravityGun::utiliser")
    {
        donjon->invoquer(heros1, c1);
        REQUIRE_NOTHROW(gravitygun1->utiliser(*donjon, c2, c1));
        REQUIRE(heros1->getPosition()==c3);
    }

    SECTION("GravityGun::accepter")
    {
        // A tester.
    }

    SECTION("GravityGun::actualiser")
    {
        REQUIRE(gravitygun1->estUtilisable());
        REQUIRE_NOTHROW(gravitygun1->utiliser(*donjon, c2, c1));
        for(size_t i = 0; i < 3; i++)
        {
            REQUIRE_FALSE(gravitygun1->estUtilisable());
            gravitygun1->actualiser();
        }
        REQUIRE(gravitygun1->estUtilisable());
    }

    SECTION("GravityGun::getPorte")
    {
        REQUIRE(gravitygun1->getPorte()==hex::Masque::contour());
    }

    SECTION("GravityGun::getZoneDegat")
    {
        hex::Masque m1;
        hex::Masque m2 = m1 + c2;
        hex::Masque m3 = m1 + c3;
        REQUIRE(gravitygun1->getZoneDegat(c3)==m3);
        REQUIRE(gravitygun1->getZoneDegat(c2)==m2);
        REQUIRE_THROWS(gravitygun1->getZoneDegat(c1)==m1);
    }
}
