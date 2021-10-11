#ifndef GUERRIER_HPP
#define GUERRIER_HPP

#include "data.hpp"
#include "player.hpp"

class Guerrier:  public Player{

	protected:

	public:

		Guerrier(const string id);

		//Affichage:
		void afficher(SDL_Renderer* pRenderer);

};

#endif
