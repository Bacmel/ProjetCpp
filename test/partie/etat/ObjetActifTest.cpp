#include "partie/etat/ObjetActif.hpp"
#include "catch.hpp"
#include "obj/Taser.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "per/Fantassin.hpp"

using namespace partie::etat;
using namespace std;

TEST_CASE("Creation et manipulation de ObjetActif", "[ObjetActif]")
{
    size_t indice = 0;
    per::APersonnage_S perso = make_shared<per::Fantassin>();
    obj::IObjet_S objet = make_shared<obj::Taser>();
    IEtat_S etat = std::make_shared<ObjetActif>(indice, perso, objet);

    SECTION("ObjetActif::getEquipeCourante") { REQUIRE(etat->getEquipeCourante() == indice); }

    SECTION("ObjetActif::getPersoSelect") { REQUIRE_NOTHROW(etat->getPersoSelect()); }

    SECTION("ObjetActif::getObjetSelect") { REQUIRE_NOTHROW(etat->getObjetSelect()); }
}

TEST_CASE("Operation de ObjetActif", "[ObjetActif]")
{
    size_t indice = 0;
    per::APersonnage_S perso = make_shared<per::Fantassin>();
    obj::IObjet_S objet = make_shared<obj::Taser>();
    IEtat_S etat = std::make_shared<ObjetActif>(indice, perso, objet);
    partie::strat::IStrategie_S strat = std::make_shared<partie::strat::JoueurHumain>();
    partie::Partie partie(strat);
    partie.setEtat(etat);
    SECTION("Operation avec Coordonnees") { REQUIRE_NOTHROW(etat->operation(partie, hex::Coordonnees())); }
    SECTION("Operation avec Indice Objet") { REQUIRE_NOTHROW(etat->operation(partie, 0)); }
    SECTION("Operation par defaut") { REQUIRE_THROWS(etat->operation(partie)); }
}