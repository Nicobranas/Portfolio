#include "laser.hpp"

Laser::Laser(const string id, int x, int y, int degats){		//id["l"][Player num][laser num]

	this->id=id;
	this->degats=degats;
	//this-> pdv = 1;

	if (id[0]!='l') throw (runtime_error("laser id have to begin per 'l'"));
	if (!(id[1]=='0' || id[1]=='1' || id[1]=='2')) throw (runtime_error("laser id[1] have to be 0,1,2 (number of the player attacking)"));

	this->lim[0]=-LARGEUR_LASER;
	this->lim[1]=LARGEUR_TERRAIN;
	this->lim[2]=-HAUTEUR_LASER;
	this->lim[3]=HAUTEUR_TERRAIN;

	int pos[2]={x,y};

	if (id[1]=='1'){
		pos[1]=pos[1]+HAUTEUR_GUERRIER-HAUTEUR_LASER;
		this->speed=-8;
	}
	if (id[1]=='2'){
		this->speed=8;
	}

	SDL_Rect box{pos[0], pos[1], LARGEUR_LASER, HAUTEUR_LASER};
	this->hitBox=box;
}

bool Laser::traj(){
	Entite::u();
	return testLim();
}

void Laser::afficher(SDL_Renderer* pRenderer)
{
	//SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(pRenderer, &this->get_hitBox());
	SDL_RenderFillRect(pRenderer, &this->get_hitBox());
    SDL_RenderCopy(pRenderer, NULL, NULL, &this->get_hitBox());
}
