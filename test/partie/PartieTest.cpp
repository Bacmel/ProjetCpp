#include "partie/Partie.hpp"
#include <iostream>
#include <map>
#include <vector>
#include "catch.hpp"
#include "donjon/Donjon.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/ICarte.hpp"
#include "obj/GravityGun.hpp"
#include "partie/etat/ObjetActif.hpp"
#include "partie/etat/PersoActif.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "per/Heros.hpp"

using namespace partie;
using namespace partie::strat;
using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace per;
using namespace std;

TEST_CASE("Creation de Partie", "[partie]")
{
    IStrategie_S strat = IStrategie_S(new JoueurHumain());
    Partie partie(strat);
    partie.genererEquipe(strat);
    IDonjon_SC donjon = partie.getDonjon();
    APersonnage_S h1(new Heros(3));
    APersonnage_S h2(new Heros(1));
    IObjet_S o1(new GravityGun);
    IObjet_S o2(new GravityGun);
    REQUIRE(donjon->getNbPersonnages() == 0);

    SECTION("Partie::genererPersonnage")
    {
        // Generation dans une equipe inexistante.
        REQUIRE_THROWS(partie.genererPersonnage(h1, 2));

        // Generation d'un personnage plusieur fois.
        partie.genererPersonnage(h1, 0);
        REQUIRE_THROWS(partie.genererPersonnage(h1, 0));
        REQUIRE_THROWS(partie.genererPersonnage(h1, 1));
    }

    SECTION("Partie::genererObjet")
    {
        // Generation d'un objet plusieur fois.
        partie.genererObjet(o1);
        REQUIRE_NOTHROW(partie.genererObjet(o1));

        // Generation dans une carte sarturee.
        size_t size = donjon->getCaseVide().size();
        for (size_t i = 0; i < size; i++)
        {
            REQUIRE_NOTHROW(partie.genererObjet(IObjet_S(new GravityGun)));
        }
        REQUIRE_THROWS(partie.genererObjet(o2));
    }

    SECTION("Partie::indiceEquipe")
    {
        // Personnage non présent.
        REQUIRE_THROWS(partie.indiceEquipe(h1));
        // Invocation du personnage.
        partie.genererPersonnage(h1, 0);
        REQUIRE(partie.indiceEquipe(h1) == 0);
    }

    SECTION("Partie::indiceGagnant")
    {
        // Cas Egalité : deux équipes vide.
        REQUIRE(partie.indiceGagnant() == -1);
        partie.genererPersonnage(h1, 0);
        REQUIRE(partie.indiceGagnant() == 0);
        partie.genererPersonnage(h2, 1);
        // Partie en cours.
        REQUIRE_THROWS(partie.indiceGagnant());
    }

    SECTION("Partie::getPersoSelect")
    {
        REQUIRE_THROWS(partie.getPersoSelect());
        REQUIRE_NOTHROW(partie.setEtat(make_shared<etat::PersoActif>(0, h1)));
        REQUIRE_NOTHROW(partie.getPersoSelect());
    }

    SECTION("Partie::getObjetSelect")
    {
        REQUIRE_THROWS(partie.getObjetSelect());
        REQUIRE_NOTHROW(partie.setEtat(make_shared<etat::ObjetActif>(0, h1, o1)));
        REQUIRE_NOTHROW(partie.getObjetSelect());
    }

    SECTION("Partie::coordonneesLibre")
    {
        size_t s = donjon->getCaseVide().size();
        for(size_t i = 0; i < s; i++)
        {
            REQUIRE_NOTHROW(partie.coordonneesLibre());
            REQUIRE_NOTHROW(partie.genererObjet(o1));
        }
        REQUIRE_THROWS(partie.coordonneesLibre());
        REQUIRE_THROWS(partie.genererObjet(o1));
    }
}