#include "hex/IterateurCarteHexagone.hpp"
#include "catch.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"

using namespace hex;

TEST_CASE("Creation, operation et manipulation des iterateurCarteHexagone", "[iterateurCarteHexagone]")
{

    CarteHexagone<bool> ch1(10); // Disque de diametre 21 cases
    ch1.remplir(true);
    IIterator_S<Coordonnees> itr = ch1.iterateur();

    SECTION("iterator")
    {
        for (Coordonnees coordonnees; itr->aSuite(); coordonnees = itr->suite())
        {
            REQUIRE(ch1(coordonnees));
        }
    }
}
