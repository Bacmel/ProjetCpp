#include "partie/etat/SelectionAuto.hpp"
#include "catch.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de SelectionAuto", "[SelectionAuto]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<SelectionAuto>(indice);

    SECTION("SelectionAuto::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("SelectionAuto::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("SelectionAuto::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de SelectionAuto", "[SelectionAuto]")
{
    SECTION("Operation avec Coordonnees") {}
}