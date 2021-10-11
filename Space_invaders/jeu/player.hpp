#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "data.hpp"
#include "entite.hpp"

class Player:  public Entite{

	protected:
		int cadence;			//shot per ms

	public:

		Player(const string id, int largeur, int hauteur);
		~Player();

		//Getters and Setters:
		const int& get_cadence() const{return this->cadence;}
		int& get_cadence() {return this->cadence;}

		//Affichage:
		virtual void afficher(SDL_Renderer* pRenderer){}

		//Movements:
		bool testLim();

		void r();					//u=up,d=down,l=left,r=right
		void l();
		void u();
		void d();
};

#endif
