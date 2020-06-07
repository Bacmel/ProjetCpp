#include "vue/PersonnageDessinable.hpp"
#include "catch.hpp"

using namespace vue;

TEST_CASE("Creation et utilisation de PersonnageDessinable", "[PersonnageDessinable]")
{
    PersonnageDessinable pd(5);
    per::APersonnage_S heros = std::make_shared<per::Heros>(3);
    per::APersonnage_S fantassin = std::make_shared<per::Fantassin>();
    REQUIRE(pd.getCote()==5);

    SECTION("PersonnageDessinable::setcote") { REQUIRE_NOTHROW(pd.setCote(3)); }

    SECTION("PersonnageDessinable::setElement")
    {
        REQUIRE_NOTHROW(pd.setElement(heros));
        REQUIRE_NOTHROW(pd.setElement(fantassin));
    }
    
    SECTION("PersonnageDessinable::visite")
    {
        per::Heros heros2(3);
        per::Fantassin fantassin2;
        REQUIRE_NOTHROW(pd.visiter(heros2));
        REQUIRE_NOTHROW(pd.visiter(fantassin2));
    }

    SECTION("PersonnageDessinable::draw")
    {
        sf::RenderTexture target;
        REQUIRE(target.create(500, 500));
        REQUIRE_NOTHROW(target.draw(pd));
    }
}