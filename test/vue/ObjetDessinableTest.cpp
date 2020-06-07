#include "vue/ObjetDessinable.hpp"
#include "catch.hpp"

using namespace vue;

TEST_CASE("Creation et utilisation de ObjetDessinable", "[ObjetDessinable]")
{
    ObjetDessinable od(5);
    obj::IObjet_S gravitygun = std::make_shared<obj::GravityGun>();
    obj::IObjet_S taser = std::make_shared<obj::Taser>();
    REQUIRE(od.getCote()==5);

    SECTION("ObjetDessinable::setcote") { REQUIRE_NOTHROW(od.setCote(3)); }

    SECTION("ObjetDessinable::setElement")
    {
        REQUIRE_NOTHROW(od.setElement(gravitygun));
        REQUIRE_NOTHROW(od.setElement(taser));
    }

    SECTION("ObjetDessinable::setColor") { REQUIRE_NOTHROW(od.setColor(sf::Color::Black)); }

    SECTION("ObjetDessinable::visite")
    {
        obj::GravityGun gravitygun2;
        obj::Taser taser2;
        REQUIRE_NOTHROW(od.visiter(gravitygun2));
        REQUIRE_NOTHROW(od.visiter(taser2));
    }

    SECTION("ObjetDessinable::draw")
    {
        sf::RenderTexture target;
        REQUIRE(target.create(500, 500));
        REQUIRE_NOTHROW(target.draw(od));
    }
}
