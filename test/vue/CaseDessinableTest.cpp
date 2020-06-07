#include "vue/CaseDessinable.hpp"
#include "catch.hpp"
#include "vue/PartieDessinable.hpp"

using namespace vue;

TEST_CASE("Construction et Manipulation de CaseDessinable", "[CaseDessinable]")
{
    CaseDessinable cd(5);
    donjon::cases::ACase_S sol = std::make_shared<donjon::cases::Sol>();
    donjon::cases::ACase_S trou = std::make_shared<donjon::cases::Trou>();

    SECTION("CaseDessinable::setcote") { REQUIRE_NOTHROW(cd.setCote(3)); }

    SECTION("CaseDessinable::setElement")
    {
        REQUIRE_NOTHROW(cd.setElement(sol));
        REQUIRE_NOTHROW(cd.setElement(trou));
    }

    SECTION("CaseDessinable::surligner") { REQUIRE_NOTHROW(cd.surligner()); }

    SECTION("CaseDessinable::visite")
    {
        donjon::cases::Sol sol2;
        donjon::cases::Trou trou2;
        REQUIRE_NOTHROW(cd.visiter(sol2));
        REQUIRE_NOTHROW(cd.visiter(trou2));
    }

    SECTION("CaseDessinable::draw")
    {
        sf::RenderTexture target;
        REQUIRE(target.create(500, 500));
        REQUIRE_NOTHROW(target.draw(cd));
    }
}