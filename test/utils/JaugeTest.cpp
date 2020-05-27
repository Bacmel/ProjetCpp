#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "utils/Jauge.hpp"

using namespace utils;

TEST_CASE( "Creation, operation et manipulation des jauges", "[jauge]" ) {

    Jauge j1(42);
    Jauge j2(0);

    REQUIRE(j1.getVal() == 42);
    REQUIRE(j1.getValMax() == 42);
    
    REQUIRE(j2.getVal() == 0);
    REQUIRE(j2.getValMax() == 0);

    SECTION( "ajouterValeur" )
    {
        j2.ajouterValeur(12);
        REQUIRE(j2.getVal() == 42);
        REQUIRE(j2.getValMax() == 42);

        j2.ajouterValeur(-12);
        REQUIRE(j2.getVal() == 30);
        REQUIRE(j2.getValMax() == 42);

        REQUIRE_THROWS(j1.ajouterValeur(-1));
        REQUIRE(j1.getVal() == 0);
        REQUIRE(j1.getValMax() == 0);
    }
    
    SECTION( "ajouterValeurMax" )
    {
        j2.ajouterValeurMax(12);
        REQUIRE(j2.getVal() == 64);
        REQUIRE(j2.getValMax() == 64);

        j2.ajouterValeur(-12);
        REQUIRE(j2.getVal() == 42);
        REQUIRE(j2.getValMax() == 64);

        REQUIRE_THROWS(j1.ajouterValeur(-1));
        REQUIRE(j1.getVal() == 0);
        REQUIRE(j1.getValMax() == 0);
    }
    
    SECTION( "remplir et vider" )
    {
        j2.vider();
        REQUIRE(j2.getVal() == 0);
        REQUIRE(j2.getValMax() == 42);

        j2.remplir();
        REQUIRE(j2.getVal() == 42);
        REQUIRE(j2.getValMax() == 64);

        j1.remplir();
        REQUIRE(j1.getVal() == 0);
        REQUIRE(j1.getValMax() == 0);

        j1.vider();
        REQUIRE(j1.getVal() == 0);
        REQUIRE(j1.getValMax() == 0);
    }
}