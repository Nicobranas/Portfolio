#ifndef MECHANT_HPP
#define MECHANT_HPP

#include "entite.hpp"
#include "data.hpp"

class Mechant : virtual public Entite{

	protected:
		string direction;

	public:
		Mechant(const string id);

		//Affichage:
		void afficher(SDL_Renderer* pRenderer);

		//Deplacement:
		void purchase();
		bool traj();
};

void spawn_inital(int nb_mechant, SDL_Renderer pRenderer);

#endif
