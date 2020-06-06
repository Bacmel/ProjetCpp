#include "partie/etat/SelectionMan.hpp"
#include "catch.hpp"s

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de SelectionMan", "[SelectionMan]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<SelectionMan>(indice);

    SECTION("SelectionMan::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("SelectionMan::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("SelectionMan::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de SelectionMan", "[SelectionMan]")
{
    SECTION("Operation avec Coordonnees") {}
}