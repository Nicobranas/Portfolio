//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "player.hpp"
#include "data.hpp"


TEST_CASE("Cosntructeur Player")
{
  Player joueur1 = Player("p1", LARGEUR_LUTIN, HAUTEUR_LUTIN);
  REQUIRE(joueur1.testLim() == true);

}
