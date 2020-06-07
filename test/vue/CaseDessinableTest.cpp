#include "vue/CaseDessinable.hpp"
#include "catch.hpp"
#include "vue/PartieDessinable.hpp"

using namespace vue;

TEST_CASE("Construction et Manipulation de CaseDessinable", "[CaseDessinable]")
{
    CaseDessinable cd(5);
    donjon::cases::Sol sol;
    donjon::cases::Trou trou;

    SECTION("CaseDessinable::setcote") { REQUIRE_NOTHROW(cd.setCote(3)); }

    SECTION("CaseDessinable::setElement")
    {
        REQUIRE_NOTHROW(cd.setElement(sol));
        REQUIRE_NOTHROW(cd.setElement(trou));
    }

    SECTION("CaseDessinable::surligner") { REQUIRE_NOTHROW(cd.surligner()); }

    SECTION("CaseDessinable::visite")
    {
        REQUIRE_NOTHROW(cd.visite(sol));
        REQUIRE_NOTHROW(cd.visite(trou));
    }

    SECTION("CaseDessinable::draw")
    {
        std::shared_ptr<vue::PartieDessinable> target = std::make_shared<vue::PartieDessinable>(25);
        sf::RenderStates states;
        REQUIRE_NOTHROW(cd.draw(target, states));
    }

    SECTION("CaseDessinable::actualiser")
    {
        REQUIRE_NOTHROW(cd.actualiser(sol));
        REQUIRE_NOTHROW(cd.actualiser(trou));
    }
}