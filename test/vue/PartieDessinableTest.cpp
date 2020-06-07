#include "vue/PartieDessinable.hpp"
#include "catch.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"

using namespace vue;

TEST_CASE("Creation et utilisation de PartieDessinable", "[PartieDessinable]")
{
    partie::strat::IStrategie_S strat = std::make_shared<partie::strat::JoueurHumain>();
    std::shared_ptr<partie::Partie> partie = std::make_shared<partie::Partie>(strat);
    partie->genererEquipe(strat);

    PartieDessinable pd(5, partie);
    
    SECTION("PartieDessinable::getCaseInventaire")
    { 
        REQUIRE_NOTHROW(pd.getCaseInventaire(0));
        REQUIRE_NOTHROW(pd.getCaseInventaire(42)); // ;)
    }

    SECTION("PartieDessinable::setElement")
    {
        partie::strat::IStrategie_S strat2 = std::make_shared<partie::strat::JoueurHumain>();
        std::shared_ptr<partie::Partie> partie2 = std::make_shared<partie::Partie>(strat);
        partie2->genererEquipe(strat2);
        REQUIRE_NOTHROW(pd.setElement(partie2));
    }

    SECTION("PartieDessinable::draw")
    {
        sf::RenderTexture target;
        REQUIRE(target.create(500, 500));
        REQUIRE_NOTHROW(target.draw(pd));
    }
}