#include "hex/Masque.hpp"
#include "catch.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"

using namespace hex;

TEST_CASE("Creation et egalite de masque", "[masque]")
{
    Masque m1(2);
    m1.remplir(true);
    Masque m2(2);
    m2.remplir(false);

    REQUIRE(m1(Coordonnees()));
    REQUIRE_FALSE(m2(Coordonnees()));

    SECTION("operator||")
    {
        Masque m3(m1 || m2);
        REQUIRE(m3(Coordonnees()));
    }

    SECTION("operator&&")
    {
        Masque m3(m1 && m2);
        REQUIRE_FALSE(m3(Coordonnees()));
    }

    SECTION("operator!")
    {
        m1 = !m1;
        REQUIRE_FALSE(m1(Coordonnees()));
    }
}
