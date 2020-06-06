#include "obj/Taser.hpp"
#include <memory>
#include "catch.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "donjon/cases/Sol.hpp"
#include "hex/CarteHexagone.hpp"
#include "per/Heros.hpp"

using namespace obj;

TEST_CASE("Creation et manipulation de Taser", "[Taser]")
{
    IObjet_S taser1 = std::make_shared<Taser>();
    hex::ICarte_S<donjon::cases::ICase_S> carte = std::make_shared<hex::CarteHexagone<donjon::cases::ICase_S>>(5);
    carte->remplir(std::make_shared<donjon::cases::Sol>());
    donjon::IDonjon_S donjon = std::make_shared<donjon::Donjon>(carte);
    hex::Coordonnees c1;
    hex::Coordonnees c2 = hex::Coordonnees::direction(hex::Direction::Sud);
    hex::Coordonnees c3 = hex::Coordonnees::direction(hex::Direction::Nord);
    per::APersonnage_S heros1 = std::make_shared<per::Heros>(3);

    SECTION("Taser::estUtilisable")
    {
        REQUIRE(taser1->estUtilisable());
        REQUIRE_NOTHROW(taser1->utiliser(*donjon, c2, c1));
        REQUIRE(taser1->estUtilisable());
    }

    SECTION("Taser::utiliser")
    {
        donjon->invoquer(heros1, c1);
        REQUIRE_NOTHROW(taser1->utiliser(*donjon, c2, c1));
        REQUIRE(heros1->getSante() == 2);
    }

    SECTION("Taser::accepter")
    {
        // A tester.
    }

    SECTION("Taser::actualiser")
    {
        REQUIRE(taser1->estUtilisable());
        REQUIRE_NOTHROW(taser1->utiliser(*donjon, c2, c1));
        taser1->actualiser();
        REQUIRE(taser1->estUtilisable());
    }

    SECTION("Taser::getPorte") { REQUIRE(taser1->getPorte() == hex::Masque::contour()); }

    SECTION("Taser::getZoneDegat")
    {
        hex::Masque m1;
        hex::Masque m2 = m1 + c2;
        hex::Masque m3 = m1 + c3;
        REQUIRE(taser1->getZoneDegat(c3) == m3);
        REQUIRE(taser1->getZoneDegat(c2) == m2);
        REQUIRE_THROWS(taser1->getZoneDegat(c1) == m1);
    }
}