#include "partie/etat/Decision.hpp"
#include "catch.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de Decision", "[Decision]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<Decision>(indice);

    SECTION("Decision::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("Decision::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("Decision::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de Decision", "[Decision]")
{
    SECTION("Operation avec Coordonnees") {}
}