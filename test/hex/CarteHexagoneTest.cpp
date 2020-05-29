#include "hex/CarteHexagone.hpp"
#include "catch.hpp"
#include "hex/Coordonnees.hpp"
using namespace hex;

TEST_CASE("Creation, operation et manipulation des carteHexagones", "[carteHexagone]")
{

    CarteHexagone<bool> ch1(0); // Disque de diametre 1 cases
    CarteHexagone<bool> ch2(2); // Disque de diametre 5 cases

    REQUIRE(ch1.getRayon() == 0);

    REQUIRE(ch2.getRayon() == 2);

    SECTION("operator()")
    {
        Coordonnees c1;
        Coordonnees c2(1, 1);
        ch1(c1) = true;
        ch2(c2) = false;
        REQUIRE(ch1(c1));
        REQUIRE_THROWS(ch1(c2) = true);
        REQUIRE_FALSE(ch2(c2));
    }

    SECTION("remplir")
    {
        ch1.remplir(false);
        ch2.remplir((std::function<bool()>)[]() { return true; });
        REQUIRE_FALSE(ch1(Coordonnees()));
        REQUIRE(ch2(Coordonnees()));
    }

    SECTION("iterator")
    {
        ch1.remplir(true);
        IIterator_S<Coordonnees> itr = ch1.iterateur();
        for (Coordonnees coordonnees; itr->aSuite(); coordonnees = itr->suite())
        {
            REQUIRE(ch1(coordonnees));
        }
    }

    SECTION("copie")
    {
        CarteHexagone<bool> ch3 = ch2;
        REQUIRE(ch3(Coordonnees()) == ch2(Coordonnees()));
    }
}
