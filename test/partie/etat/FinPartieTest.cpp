#include "partie/etat/FinPartie.hpp"
#include "catch.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"

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
    size_t indice = 0;
    IEtat_S etat = std::make_shared<FinPartie>(indice);
    partie::strat::IStrategie_S strat = std::make_shared<partie::strat::JoueurHumain>();
    partie::Partie partie(strat);
    partie.setEtat(etat);
    SECTION("Operation avec Coordonnees") { REQUIRE_THROWS(etat->operation(partie, hex::Coordonnees())); }
    SECTION("Operation avec Indice Objet") { REQUIRE_THROWS(etat->operation(partie, 0)); }
    SECTION("Operation par defaut") { REQUIRE_NOTHROW(etat->operation(partie)); }
}