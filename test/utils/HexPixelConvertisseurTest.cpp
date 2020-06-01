#include "utils/HexPixelConvertisseur.hpp"
#include <cmath>
#include <iostream>
#include "catch.hpp"

using namespace hex;
using namespace sf;
using namespace utils;

TEST_CASE("Creation et manipulation de HexPixelConvertisseur", "[HexPixelConvertisseur]")
{
    HexPixelConvertisseur hpc;
    float rayon = 10;
    SECTION("Hex vers pixel")
    {
        // A l'origine
        Coordonnees origine(0, 0);
        Vector2f pixel = hpc(rayon, origine);
        REQUIRE(pixel.x == 0);
        REQUIRE(pixel.y == 0);

        // A une case quelconque (résultat calculé sur Matlab)
        Coordonnees hex(10, -1);
        pixel = hpc(rayon, hex);
        REQUIRE(pixel.x == -15);
        REQUIRE(std::abs((double)pixel.y - 164.5448) < 1e-4);
    }

    SECTION("Pixel vers Hex")
    {
        // A l'origine
        Vector2i pixel(0, 0);
        Coordonnees hex = hpc(rayon, pixel);
        REQUIRE(hex.getColonne() == 0);
        REQUIRE(hex.getLigne() == 0);

        // A une case quelconque (résultat calculé sur Matlab)
        pixel = Vector2i(-15, 165);
        hex = hpc(rayon, pixel);
        REQUIRE(hex.getColonne() == -1);
        REQUIRE(hex.getLigne() == 10);
    }
}
