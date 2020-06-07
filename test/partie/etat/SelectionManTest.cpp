#include "partie/etat/SelectionMan.hpp"
#include "catch.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"

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
    size_t indice = 0;
    IEtat_S etat = std::make_shared<SelectionMan>(indice);
    partie::strat::IStrategie_S strat = std::make_shared<partie::strat::JoueurHumain>();
    partie::Partie partie(strat);
    partie.setEtat(etat);
    SECTION("Operation avec Coordonnees") { REQUIRE_NOTHROW(etat->operation(partie, hex::Coordonnees())); }
    SECTION("Operation avec Indice Objet") { REQUIRE_THROWS(etat->operation(partie, 0)); }
    SECTION("Operation par defaut") { REQUIRE_THROWS(etat->operation(partie)); }
}