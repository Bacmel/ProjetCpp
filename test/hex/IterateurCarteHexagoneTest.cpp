#include "hex/IterateurCarteHexagone.hpp"
#include "catch.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"
#include <set>

using namespace hex;

TEST_CASE("Creation, operation et manipulation des iterateurCarteHexagone", "[iterateurCarteHexagone]")
{

    CarteHexagone<bool> ch1(10); // Disque de diametre 21 cases
    ch1.remplir(true);
    IIterator_S<Coordonnees> itr = ch1.iterateur();

    SECTION("iterator")
    {
        std::set<Coordonnees> casesVues;
        size_t nbItr(0);
        while (itr->aSuite())
        {
            Coordonnees coordonnees = itr->suite();
            nbItr++;
            casesVues.insert(coordonnees);
            REQUIRE(ch1(coordonnees));
        }
        // S'assure d'être passé sur chaque case 1 seule fois.
        REQUIRE(casesVues.size() == 331);
        REQUIRE(nbItr == 331);
    }
}
