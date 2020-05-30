#include "partie/Partie.hpp"
#include <iostream>
#include <map>
#include <vector>
#include "catch.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "hex/CarteHexagone.hpp"
#include "obj/GravityGun.hpp"
#include "per/Heros.hpp"

using namespace partie;
using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace per;
using namespace std;

TEST_CASE("Creation de Partie", "[partie]")
{
    Partie partie(2);
    IDonjon_SC donjon = partie.getDonjon();
    APersonnage_S h1(new Heros(3));
    APersonnage_S h2(new Heros(1));
    IObjet_S o1(new GravityGun);
    IObjet_S o2(new GravityGun);
    REQUIRE(donjon->getNbPersonnages()==0);

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
        REQUIRE_THROWS(partie.genererObjet(o1));

        // Generation dans une carte sarture.
        size_t size = donjon->getCaseVide().size();
        for(size_t i = 0; i < size; i++)
        {
            REQUIRE_NOTHROW(partie.genererObjet(IObjet_S(new GravityGun)));
        }
        REQUIRE_THROWS(partie.genererObjet(o2));
    }
}

TEST_CASE("Gestion de Partie", "[partie]")
{
    Partie partie(2);
    IDonjon_SC donjon = partie.getDonjon();
    APersonnage_S h1(new Heros(3));
    APersonnage_S h2(new Heros(1));
    IObjet_S o1(new GravityGun);
    IObjet_S o2(new GravityGun);

    REQUIRE(donjon->getNbPersonnages()==0);
    SECTION("Partie::deplacerPersonnage")
    {
        // Deplacer un personnage non_invoque.
        REQUIRE_THROWS(partie.deplacerPersonnage(0, h1, Deplacement::Forcer, h1->getPosition()));
        
        // Deplacer un personnage d'une autre equipe.
        partie.genererPersonnage(h1, 0);
        REQUIRE_THROWS(partie.deplacerPersonnage(1, h1, Deplacement::Forcer, h1->getPosition()));

        // Deplacement autorise.
        Coordonnees c = h1->getPosition().translate(Direction::Nord);
        partie.deplacerPersonnage(0, h1, Deplacement::Marcher, c);
        REQUIRE(h1->getPosition()==c);
    }
}
