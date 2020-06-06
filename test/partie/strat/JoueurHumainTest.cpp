#include "partie/strat/JoueurHumain.hpp"
#include <memory>
#include "catch.hpp"
#include "partie/Partie.hpp"

using namespace partie;
using namespace partie::strat;

TEST_CASE("Création de JoueurHumain", "[JoueurHumain]")
{
    IStrategie_S jh = std::make_shared<JoueurHumain>();
    Equipe equipe(jh);
    Partie partie(jh);
    REQUIRE_NOTHROW(jh->mettreEnOeuvre(partie, equipe));
}