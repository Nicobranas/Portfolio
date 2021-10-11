#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "mechant.hpp"
#include "data.hpp"

TEST_CASE("Cosntructeur Mechant")
{
  Mechant m1 = Mechant("m1");
  REQUIRE(m1.get_pdv()== 10);
  REQUIRE (m1.get_hitBox().w == LARGEUR_MECHANT);
  REQUIRE(m1.get_hitBox().h == HAUTEUR_MECHANT);
  REQUIRE( (m1.get_hitBox().x <  LARGEUR_TERRAIN - LARGEUR_MECHANT) == true);
}
