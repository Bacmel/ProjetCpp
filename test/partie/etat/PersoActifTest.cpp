#include "partie/etat/PersoActif.hpp"
#include "catch.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de PersoActif", "[PersoActif]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<PersoActif>(indice);

    SECTION("PersoActif::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("PersoActif::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("PersoActif::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de PersoActif", "[PersoActif]")
{
    SECTION("Operation avec Coordonnees") {}
}