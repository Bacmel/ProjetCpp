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
        j1.ajouterValeur(12);
        REQUIRE(j1.getVal() == 42);
        REQUIRE(j1.getValMax() == 42);

        j1.ajouterValeur(-12);
        REQUIRE(j1.getVal() == 30);
        REQUIRE(j1.getValMax() == 42);

        REQUIRE_THROWS(j2.ajouterValeur(-1));
        REQUIRE(j2.getVal() == 0);
        REQUIRE(j2.getValMax() == 0);
    }
    
    SECTION( "ajouterValeurMax" )
    {
        j1.ajouterValeurMax(12);
        REQUIRE(j1.getVal() == 54);
        REQUIRE(j1.getValMax() == 54);

        j1.ajouterValeur(-12);
        REQUIRE(j1.getVal() == 42);
        REQUIRE(j1.getValMax() == 54);

        REQUIRE_THROWS(j2.ajouterValeurMax(-1));
        j2.ajouterValeurMax(1);
        REQUIRE(j2.getVal() == 1);
        REQUIRE(j2.getValMax() == 1);
    }
    
    SECTION( "remplir et vider" )
    {
        j1.vider();
        REQUIRE(j1.getVal() == 0);
        REQUIRE(j1.getValMax() == 42);

        j1.remplir();
        REQUIRE(j1.getVal() == 42);
        REQUIRE(j1.getValMax() == 42);

        j2.remplir();
        REQUIRE(j2.getVal() == 0);
        REQUIRE(j2.getValMax() == 0);

        j2.vider();
        REQUIRE(j2.getVal() == 0);
        REQUIRE(j2.getValMax() == 0);
    }
}