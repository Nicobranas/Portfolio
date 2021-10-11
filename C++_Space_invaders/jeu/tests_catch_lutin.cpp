//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lutin.hpp"
#include "data.hpp"

TEST_CASE("Cosntructeur Lutin")
{
  Lutin l1 = Lutin("p1");
  REQUIRE(l1.get_pdv()== 80);
  REQUIRE(l1.get_degats()== 10);

  REQUIRE (l1.get_hitBox().w == LARGEUR_LUTIN);
  REQUIRE(l1.get_hitBox().h == HAUTEUR_LUTIN);
  REQUIRE( (l1.get_hitBox().x <  LARGEUR_TERRAIN - LARGEUR_LUTIN) == true);

}
