#ifndef LUTIN_HPP
#define LUTIN_HPP

#include "data.hpp"
#include "player.hpp"

class Lutin:  public Player{

	protected:

	public:

		Lutin(const string id);

		//Affichage:
		void afficher(SDL_Renderer* pRenderer);

};

#endif
