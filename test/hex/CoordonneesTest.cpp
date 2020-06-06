#include "hex/Coordonnees.hpp"
#include "catch.hpp"

using namespace hex;

TEST_CASE("Creation, operation et manipulation des coordonnees", "[coordonnees]")
{

    Coordonnees c1; // Par defaut
    Coordonnees c2(1, 2); // Ligne et colonne
    Coordonnees c3(2, 1, -3); // Coordonnees x, y et z

    SECTION("getters")
    {
        REQUIRE(c1.getLigne() == 0);
        REQUIRE(c1.getColonne() == 0);

        REQUIRE(c2.getLigne() == 1);
        REQUIRE(c2.getColonne() == 2);

        REQUIRE(c3.getX() == 2);
        REQUIRE(c3.getY() == 1);
        REQUIRE(c3.getZ() == -3);
    }

    SECTION("Coordonnees::operator+")
    {
        Coordonnees c4 = c1 + c2;
        REQUIRE(c4.getLigne() == c1.getLigne() + c2.getLigne());
        REQUIRE(c4.getColonne() == c1.getColonne() + c2.getColonne());
    }

    SECTION("Coordonnees::operator-")
    {
        Coordonnees c4 = c1 - c2;
        REQUIRE(c4.getLigne() == c1.getLigne() - c2.getLigne());
        REQUIRE(c4.getColonne() == c1.getColonne() - c2.getColonne());
    }

    SECTION("Coordonnees::operator*")
    {
        Coordonnees c4 = c3 * 2;
        REQUIRE(c4.getLigne() == 2 * c3.getLigne());
        REQUIRE(c4.getColonne() == 2 * c3.getColonne());
    }

    SECTION("Coordonnees::translater")
    {
        Coordonnees c4 = c3.translater(Direction::Nord, 2);
        REQUIRE(c4.getLigne() == c3.getLigne() - 2);
        REQUIRE(c4.getColonne() == c3.getColonne());
    }

    SECTION("Coordonnees::operator==")
    {
        REQUIRE(c2 == c3);
        REQUIRE_FALSE(c1 == c2);
    }

    SECTION("Coordonnees::operator!=")
    {
        REQUIRE(c1 != c3);
        REQUIRE_FALSE(c3 != c2);
    }

    SECTION("Coordonnees::operator>")
    {
        REQUIRE(c2 > c1);
        REQUIRE_FALSE(c3 > c2);
    }

    SECTION("Coordonnees::operator>=")
    {
        REQUIRE(c3 >= c2);
        REQUIRE_FALSE(c1 >= c2);
    }

    SECTION("Coordonnees::operator<")
    {
        REQUIRE(c1 < c2);
        REQUIRE_FALSE(c3 < c2);
    }

    SECTION("Coordonnees::operator<=")
    {
        REQUIRE(c2 <= c3);
        REQUIRE_FALSE(c2 <= c1);
    }

    SECTION("Coordonnees::longueur")
    {
        REQUIRE(c3.longueur() == 3);
        REQUIRE(c2.longueur() == 3);
        REQUIRE(c1.longueur() == 0);
    }

    SECTION("Coordonnees::distance")
    {
        REQUIRE(c2.distance(c3) == 0);
        REQUIRE(c1.distance(c2) == c2.longueur());
    }

    SECTION("Angle et direction")
    {
        Coordonnees c1(1, -3);
        Coordonnees c2 = c1.translater(Direction::Nord);
        REQUIRE(std::abs(c1.angle(c2)) < 1e-5);
        REQUIRE(c1.direction(c2) == Direction::Nord);

        c2 = c1.translater(Direction::SudEst);
        REQUIRE(std::abs(c1.angle(c2) - M_PI * 2.f / 3.f) < 1e-5);
        REQUIRE(c1.direction(c2) == Direction::SudEst);

        c2 = c2.translater(Direction::Sud);
        REQUIRE_THROWS(c1.direction(c2));
    }

    SECTION("Coordonnees::rotation")
    {
        Coordonnees c = Coordonnees::direction(Direction::NordEst);
        Coordonnees cTG = c.tournerTrigonometrique(Coordonnees());
        Coordonnees cTD = c.tournerHoraire(Coordonnees());
        REQUIRE(Coordonnees().direction(cTG) == Direction::Nord);
        REQUIRE(Coordonnees().direction(cTD) == Direction::SudEst);

        Coordonnees cTV = c.tournerVers(Coordonnees(), Direction::SudOuest, Direction::NordEst);
        REQUIRE(cTV == Coordonnees::direction(Direction::SudOuest));
    }

    SECTION("Coordonnees::arrondir")
    {
        REQUIRE_THROWS(Coordonnees::arrondir(2.33f, -1.3f, 0.f));

        Coordonnees c1 = Coordonnees::arrondir(-1.45f, 0.35f, 1.1f);
        REQUIRE(c1 == Coordonnees::arrondir(-1, 0, 1));

        Coordonnees c2 = Coordonnees::arrondir(14.7f, 9.2f);
        REQUIRE(c2 == Coordonnees::arrondir(15, 9));
    }
}
