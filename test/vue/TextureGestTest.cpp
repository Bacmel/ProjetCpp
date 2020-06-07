#include "vue/TextureGest.hpp"
#include "catch.hpp"

using namespace vue;

TEST_CASE("Creation et utilisation de TextureGest", "[TextureGest]")
{
    TextureGest& tg = TextureGest::getInstance();

    SECTION("TextureGest::obtenir")
    {
        REQUIRE_NOTHROW(tg.obtenir("ressources/textures/per/heros.png"));
        REQUIRE_THROWS(tg.obtenir("ressources/textures/per/Throws.png"));
    }

    SECTION("TextureGest::retirer")
    {
        REQUIRE_NOTHROW(tg.retirer("ressources/textures/per/heros.png"));
        REQUIRE_NOTHROW(tg.retirer("ressources/textures/per/heros.png"));
    }
}