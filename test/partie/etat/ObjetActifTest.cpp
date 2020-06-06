#include "partie/etat/ObjetActif.hpp"
#include "catch.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de ObjetActif", "[ObjetActif]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<ObjetActif>(indice);

    SECTION("ObjetActif::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("ObjetActif::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("ObjetActif::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de ObjetActif", "[ObjetActif]")
{
    SECTION("Operation avec Coordonnees") {}
}