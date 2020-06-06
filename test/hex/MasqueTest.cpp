#include "hex/Masque.hpp"
#include "catch.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"

using namespace hex;

TEST_CASE("Creation et egalite de Masque", "[Masque]")
{
    Masque m1;
    m1 = Masque::contour();
    Masque m2;
    m2 = m2 + Coordonnees();
    Masque mRot;
    mRot = mRot + Coordonnees::direction(Direction::Nord);

    REQUIRE_FALSE(m1(Coordonnees()));
    REQUIRE(m2(Coordonnees()));

    SECTION("Masque::operator||")
    {
        Masque m3(m1 || m2);
        REQUIRE(m3(Coordonnees()));
    }

    SECTION("Masque::operator&&")
    {
        Masque m3(m1 && m2);
        REQUIRE_FALSE(m3(Coordonnees()));
    }

    SECTION("Masque::operator+")
    {
        m1 = m1 + Coordonnees();
        REQUIRE(m1(Coordonnees()));
    }

    SECTION("Masque::operator-")
    {
        m2 = m2 - Coordonnees();
        REQUIRE_FALSE(m2(Coordonnees()));
    }

    SECTION("Masque::deplacer")
    {
        Masque m3 = m1.deplacer(Coordonnees().translater(Direction::Nord, 2));
        REQUIRE_FALSE(m3(Coordonnees()));
    }

    SECTION("Masque::tournerTrigonometrique")
    {
        REQUIRE(mRot(Coordonnees::direction(Direction::Nord)));
        REQUIRE_NOTHROW(mRot=mRot.tournerTrigonometrique(Coordonnees()));
        REQUIRE_FALSE(mRot(Coordonnees::direction(Direction::Nord)));
        REQUIRE(mRot(Coordonnees::direction(Direction::NordOuest)));
    }

    SECTION("Masque::tournerHoraire")
    {
        REQUIRE(mRot(Coordonnees::direction(Direction::Nord)));
        REQUIRE_NOTHROW(mRot=mRot.tournerHoraire(Coordonnees()));
        REQUIRE_FALSE(mRot(Coordonnees::direction(Direction::Nord)));
        REQUIRE(mRot(Coordonnees::direction(Direction::NordEst)));
    }

    SECTION("Masque::tournerVers")
    {
        REQUIRE(mRot(Coordonnees::direction(Direction::Nord)));
        REQUIRE_NOTHROW(mRot=mRot.tournerVers(Coordonnees(), Direction::NordOuest, Direction::Nord));
        REQUIRE_FALSE(mRot(Coordonnees::direction(Direction::Nord)));
        REQUIRE(mRot(Coordonnees::direction(Direction::NordOuest)));
        REQUIRE_NOTHROW(mRot=mRot.tournerVers(Coordonnees(), Direction::Sud, Direction::NordOuest));
        REQUIRE_FALSE(mRot(Coordonnees::direction(Direction::NordOuest)));
        REQUIRE(mRot(Coordonnees::direction(Direction::Sud)));
    }
}
