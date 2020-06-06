#include "partie/etat/SelectionAuto.hpp"
#include "catch.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"

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
    size_t indice = 0;
    IEtat_S etat = std::make_shared<SelectionAuto>(indice);
    partie::strat::IStrategie_S strat = std::make_shared<partie::strat::JoueurHumain>();
    partie::Partie partie(strat);
    partie.setEtat(etat);
    SECTION("Operation avec Coordonnees") { REQUIRE_THROWS(etat->operation(partie, hex::Coordonnees())); }
    SECTION("Operation avec Indice Objet") { REQUIRE_THROWS(etat->operation(partie, 0)); }
    SECTION("Operation par defaut") { REQUIRE_NOTHROW(etat->operation(partie)); }
}