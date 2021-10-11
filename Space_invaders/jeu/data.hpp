#ifndef DATA_HPP
#define DATA_HPP

#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <time.h>
#include <list>
#include <set>
#include <memory>
#include <SDL2/SDL_ttf.h>
#include "catch.hpp"

using namespace std;

//caracteristique terrain
#define LARGEUR_TERRAIN 900
#define HAUTEUR_TERRAIN 900
#define HAUTEUR_ZONE_MILIEU 900/3

//caractéristiques menu
#define LARGEUR_MENU 400

//caracteristqiue rectangle
#define LARGEUR_GUERRIER 60
#define HAUTEUR_GUERRIER 69

#define LARGEUR_LUTIN 60
#define HAUTEUR_LUTIN 69

//caracteristique laser
#define LARGEUR_LASER 5
#define HAUTEUR_LASER 15

#define LARGEUR_MECHANT 40
#define HAUTEUR_MECHANT 40

#endif
