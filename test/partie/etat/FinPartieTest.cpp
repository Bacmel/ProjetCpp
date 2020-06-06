#include "partie/etat/FinPartie.hpp"
#include "catch.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de FinPartie", "[FinPartie]")
{
    size_t indice = 0;
    IEtat_S etat = std::make_shared<FinPartie>(indice);

    SECTION("FinPartie::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("FinPartie::getPersoSelect") { REQUIRE_THROWS(etat->getPersoSelect()); }

    SECTION("FinPartie::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de FinPartie", "[FinPartie]")
{
    SECTION("Operation avec Coordonnees") {}
}