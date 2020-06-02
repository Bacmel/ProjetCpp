#include "donjon/Donjon.hpp"
#include <iostream>
#include <map>
#include <vector>
#include "catch.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "hex/CarteHexagone.hpp"
#include "obj/GravityGun.hpp"
#include "per/Heros.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace per;
using namespace std;

TEST_CASE("Creation et manipulation de Donjon", "[Donjon]")
{
    ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(2));
    function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
    carte->remplir(fournisseurSol);
    Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
    (*carte)(positionTrou) = ICase_S(new Trou());
    Donjon donjon(carte);

    SECTION("Donjon::invoquer")
    {
        // Invocation sur une case valide.
        APersonnage_S heros(new Heros(3));
        Coordonnees pos(-1, 2);
        REQUIRE_NOTHROW(donjon.invoquer(heros, pos));
        REQUIRE(heros->getPosition() == pos);
        // Invocation sur une case occupée.
        APersonnage_S herosBis(new Heros(2));
        REQUIRE_THROWS(donjon.invoquer(herosBis, pos));
        // Invocation sur une case invalide.
        REQUIRE_THROWS(donjon.invoquer(herosBis, positionTrou));
        // Invocation d'un personnage déjà présent.
        REQUIRE_THROWS(donjon.invoquer(heros, Coordonnees().translate(Direction::Sud)));
    }

    SECTION("Donjon::deplacer")
    {
        // Invocation sur une case valide.
        APersonnage_S heros(new Heros(3));
        Coordonnees pos(0, 0);
        donjon.invoquer(heros, pos);
        // Déplacement vers une case interdite.
        REQUIRE_THROWS(donjon.deplace(*heros, Deplacement::Forcer, pos.translate(Direction::Nord)));
        // Déplacement hors carte.
        REQUIRE_THROWS(donjon.deplace(*heros, Deplacement::Forcer, pos.translate(Direction::NordEst, 4)));
        // Déplacement vers une case occupée.
        APersonnage_S herosBis(new Heros(1));
        Coordonnees posBis = pos.translate(Direction::Sud);
        donjon.invoquer(herosBis, posBis);
        REQUIRE_THROWS(donjon.deplace(*heros, Deplacement::Forcer, posBis));
        // Déplacement valide
        Coordonnees destination = pos.translate(Direction::NordEst);
        REQUIRE_NOTHROW(donjon.deplace(*heros, Deplacement::Forcer, destination));
        REQUIRE(heros->getPosition() == destination);
    }

    SECTION("Donjon::pousse")
    {
        APersonnage_S heros(new Heros(4));
        Coordonnees pos;
        donjon.invoquer(heros, pos);
        // Pousse vers une case libre.
        map<Coordonnees, Direction> aoe;
        aoe.insert(pair<Coordonnees, Direction>(pos, Direction::Sud));
        donjon.pousse(aoe, 1);
        REQUIRE(heros->getPosition() == pos.translate(Direction::Sud));
        // Pousse vers une case interdite.
        aoe = map<Coordonnees, Direction>();
        aoe.insert(pair<Coordonnees, Direction>(pos.translate(Direction::Sud), Direction::Nord));
        donjon.pousse(aoe, 2);
        REQUIRE(heros->getPosition() == positionTrou);
        // Pousse vers une case occupée.
        heros = make_shared<Heros>(3);
        donjon.invoquer(heros, pos);
        APersonnage_S herosBis = make_shared<Heros>(2);
        donjon.invoquer(herosBis, pos.translate(Direction::NordEst));
        aoe = map<Coordonnees, Direction>();
        aoe.insert(pair<Coordonnees, Direction>(pos, Direction::NordEst));
        REQUIRE(heros->getPosition() == pos);
        REQUIRE(heros->getSante() == heros->getSanteMax());
        // Pousse hors du terrain.
        aoe = map<Coordonnees, Direction>();
        aoe.insert(pair<Coordonnees, Direction>(pos, Direction::Sud));
        donjon.pousse(aoe, 15);
        REQUIRE(heros->getPosition() == pos.translate(Direction::Sud, 2));
        REQUIRE(heros->getSante() == heros->getSanteMax() - 1);
    }

    SECTION("Donjon::degat")
    {
        APersonnage_S heros = make_shared<Heros>(4);
        Coordonnees pos;
        donjon.invoquer(heros, pos);
        // Dégat à côté du héros.
        map<Coordonnees, size_t> aoe;
        aoe.insert(pair<Coordonnees, size_t>(pos.translate(Direction::NordEst), 1));
        donjon.degat(aoe);
        REQUIRE(heros->getSante() == heros->getSanteMax());
        // Dégat sur le héros.
        aoe.insert(pair<Coordonnees, size_t>(pos, 1));
        donjon.degat(aoe);
        REQUIRE(heros->getSante() == heros->getSanteMax() - 1);
    }

    SECTION("Donjon::deposer")
    {
        IObjet_S objet = make_shared<GravityGun>();
        Coordonnees pos(0, 0);
        // Déposer sur une case vide.
        REQUIRE_NOTHROW(donjon.deposer(objet, pos));
        // Déposer sur une case occupée.
        objet = make_shared<GravityGun>();
        REQUIRE_THROWS(donjon.deposer(objet, pos));
    }

    SECTION("Donjon::ramaser")
    {
        IObjet_S objet = make_shared<GravityGun>();
        Coordonnees pos(2, -1);
        // Ramasser un objet sur une case vide.
        REQUIRE_THROWS(donjon.ramasser(pos));
        // Ramasser un objet sur une case pleine.
        donjon.deposer(objet, pos);
        IObjet_S objObtenu = donjon.ramasser(pos);
        REQUIRE(objet == objObtenu);
    }
}
