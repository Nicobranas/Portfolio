#ifndef LASER_HPP
#define LASER_HPP

#include "entite.hpp"
#include "data.hpp"

class Laser : virtual public Entite{

	protected:

	public:

		Laser(const string id, int x, int y, int degats);

		//Deplacement:
		bool traj();

		//Affichage:
		void afficher(SDL_Renderer* pRenderer);

		//getters:



};

#endif
