#include "hex/Masque.hpp"
#include "catch.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"

using namespace hex;

TEST_CASE("Creation et egalite de masque", "[masque]")
{
    Masque m1;
    m1 = m1 + Coordonnees::direction(Direction::Nord);
    m1 = m1 + Coordonnees::direction(Direction::NordEst);
    m1 = m1 + Coordonnees::direction(Direction::SudEst);
    m1 = m1 + Coordonnees::direction(Direction::Sud);
    m1 = m1 + Coordonnees::direction(Direction::SudOuest);
    m1 = m1 + Coordonnees::direction(Direction::NordOuest);
    Masque m2;
    m2 = m2 + Coordonnees();

    REQUIRE_FALSE(m1(Coordonnees()));
    REQUIRE(m2(Coordonnees()));

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

    SECTION("operator+")
    {
        m1 = m1 + Coordonnees();
        REQUIRE(m1(Coordonnees()));
    }

    SECTION("operator-")
    {
        m2 = m2 - Coordonnees();
        REQUIRE_FALSE(m2(Coordonnees()));
    }

    SECTION("deplacer")
    {
        Masque m3 = m1.deplacer(Coordonnees().translate(Direction::Nord, 2));
        REQUIRE_FALSE(m3(Coordonnees()));
    }
}
