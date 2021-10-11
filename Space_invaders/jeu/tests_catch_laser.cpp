#include "laser.hpp"
#include "data.hpp"
#include "catch.hpp"

TEST_CASE("Constructeur Laser")
{
  Laser l1 = Laser("l1", 0, 10, 5);

  REQUIRE(l1.get_hitBox().w == LARGEUR_LASER);
  REQUIRE(l1.get_hitBox().h == HAUTEUR_LASER);
  REQUIRE(l1.get_hitBox().x == 0);
  REQUIRE(l1.get_hitBox().y == 10+HAUTEUR_GUERRIER-HAUTEUR_LASER);


  REQUIRE(l1.testLim() == true);

  Laser l2 = Laser("l2", 0, 10, 5);

  REQUIRE(l2.get_hitBox().w == LARGEUR_LASER);
  REQUIRE(l2.get_hitBox().h == HAUTEUR_LASER);
  REQUIRE(l2.get_hitBox().x == 0);
  REQUIRE(l2.get_hitBox().y == 10);


  REQUIRE(l2.testLim() == true);

}
