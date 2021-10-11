#include "catch.hpp"
#include "interface.hpp"
#include "data.hpp"

TEST_CASE("Constructeur Interface")
{
  Interface* interface = new Interface();
  REQUIRE(interface->get_zone_milieu().x == 0);
  REQUIRE(interface->get_zone_milieu().y == (HAUTEUR_TERRAIN - HAUTEUR_ZONE_MILIEU)/2);
  REQUIRE(interface->get_zone_milieu().w == LARGEUR_TERRAIN);
  REQUIRE(interface->get_zone_milieu().h == HAUTEUR_ZONE_MILIEU);
  //delete interface;
}
