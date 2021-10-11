//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "guerrier.hpp"
#include "data.hpp"

TEST_CASE("Cosntructeur Guerrier")
{
  Guerrier g1 = Guerrier("p1");
  REQUIRE(g1.get_pdv()== 100);
  REQUIRE(g1.get_degats()== 15);

  REQUIRE (g1.get_hitBox().w == LARGEUR_GUERRIER);
  REQUIRE(g1.get_hitBox().h == HAUTEUR_GUERRIER);
  REQUIRE( (g1.get_hitBox().x <  LARGEUR_TERRAIN - LARGEUR_GUERRIER) == true);

}
