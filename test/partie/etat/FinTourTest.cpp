#include "partie/etat/FinTour.hpp"
#include "catch.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de FinTour", "[FinTour]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<FinTour>(indice);

    SECTION("FinTour::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("FinTour::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("FinTour::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de FinTour", "[FinTour]")
{
    SECTION("Operation avec Coordonnees") {}
}