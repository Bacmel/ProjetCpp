#include "per/Heros.hpp"
#include "catch.hpp"

using namespace per;

TEST_CASE("Creation et manipulation de Heros", "[Heros]")
{
    Heros heros(3);

    SECTION("APersonnage::estVivant")
    {
        REQUIRE(heros.estVivant());
        // Tue le héros.
        heros.setSante(0);
        REQUIRE_FALSE(heros.estVivant());
        // Tue le héros par sa santé maximale.
        heros.setSante(3);
        heros.setSanteMax(0);
        REQUIRE_FALSE(heros.estVivant());
    }

    SECTION("APersonnage::setSante")
    {
        // Santé supérieur au maximum impossible.
        heros.setSante(heros.getSanteMax() + 1);
        REQUIRE(heros.getSante() == heros.getSanteMax());
    }

    SECTION("APersonnage::setSanteMax")
    {
        heros.setSanteMax(2);
        REQUIRE(heros.getSanteMax() == 2);
        REQUIRE(heros.getSante() <= heros.getSanteMax());
    }

    SECTION("APersonnage::getId")
    {
        Heros heros2(3);
        REQUIRE(heros.getId() != heros2.getId());
    }

    SECTION("APersonnage::subitAttaque")
    {
        heros.subitAttaque(1);
        REQUIRE(heros.getSante() == heros.getSanteMax() - 1);
    }

    // TODO ajouter des tests pour les objets
}
