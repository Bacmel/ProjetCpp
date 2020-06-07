#include "partie/etat/PersoActif.hpp"
#include "catch.hpp"
#include "per/Fantassin.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de PersoActif", "[PersoActif]")
{
    size_t indice = 0;
    per::APersonnage_S perso = make_shared<per::Fantassin>();
    IEtat_S etat = std::make_shared<PersoActif>(indice, perso);

    SECTION("PersoActif::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("PersoActif::getPersoSelect") { REQUIRE_NOTHROW(etat->getPersoSelect()); }

    SECTION("PersoActif::getObjetSelect") { REQUIRE_THROWS(etat->getObjetSelect()); }
}

TEST_CASE("Operation de PersoActif", "[PersoActif]")
{
    size_t indice = 0;
    per::APersonnage_S perso = make_shared<per::Fantassin>();
    IEtat_S etat = std::make_shared<PersoActif>(indice, perso);
    partie::strat::IStrategie_S strat = std::make_shared<partie::strat::JoueurHumain>();
    partie::Partie partie(strat);
    partie.setEtat(etat);
    SECTION("Operation avec Coordonnees") { REQUIRE_NOTHROW(etat->operation(partie, hex::Coordonnees())); }
    SECTION("Operation avec Indice Objet") { REQUIRE_NOTHROW(etat->operation(partie, 0)); }
    SECTION("Operation par defaut") { REQUIRE_THROWS(etat->operation(partie)); }
}