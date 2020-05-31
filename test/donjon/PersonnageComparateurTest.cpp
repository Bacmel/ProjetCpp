#include "donjon/PersonnageComparateur.hpp"
#include <memory>
#include "catch.hpp"
#include "per/Heros.hpp"

using namespace donjon;
using namespace per;
using namespace std;

TEST_CASE("Creation et manipulation de PersonnageComparateur", "[PersonnageComparateur]")
{
    PersonnageComparateur pc;

    APersonnage_S heros1 = make_shared<Heros>(3);
    APersonnage_S heros2 = make_shared<Heros>(3);
    APersonnage_S perNull;
    // Comparaison au pointeur null.
    REQUIRE_THROWS(pc(perNull, heros1));
    REQUIRE_THROWS(pc(heros1, perNull));
    // Comparaison entre deux personnages par leur Id.
    REQUIRE(pc(heros1, heros2) == (heros1->getId() < heros2->getId()));
    REQUIRE(pc(heros2, heros1) == (heros1->getId() > heros2->getId()));
    // Comparaison avec le même personnage.
    REQUIRE_FALSE(pc(heros2, heros2));
}
