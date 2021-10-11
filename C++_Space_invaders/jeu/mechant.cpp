#include "mechant.hpp"


Mechant::Mechant(const string id){		//id["l"][Player num][laser num]

	this->id=id;
	this->degats=25;
	this->pdv=10;
	this-> speed=5;

	if (id[0]!='m') throw (runtime_error("mechant id have to begin per 'm'"));
	if (!(id[1]=='0' || id[1]=='1' || id[1]=='2')) throw (runtime_error("mechant id[1] have to be 0,1,2 (number of the player who is attacked)"));


	this->lim[0]=-LARGEUR_MECHANT;
	this->lim[1]=LARGEUR_TERRAIN;
	this->lim[2]=-HAUTEUR_MECHANT;
	this->lim[3]=HAUTEUR_TERRAIN;

	int x = (unsigned int)(clock()*clock())%(LARGEUR_TERRAIN - LARGEUR_MECHANT);
	int y = (HAUTEUR_TERRAIN-HAUTEUR_ZONE_MILIEU)/2 + (unsigned int)(clock()*clock())%(HAUTEUR_ZONE_MILIEU - HAUTEUR_MECHANT);
	SDL_Rect box{x, y , LARGEUR_MECHANT, HAUTEUR_MECHANT};
	this->hitBox=box;

	if (id[1]=='2')	//les mechant du haut sont les mechant 2 et les mechant du bas sont les mechant 1
		this->direction="left";


	else if (id[1]=='1')
		this->direction="right";

}

void Mechant::purchase()
{
	//if(id[1] =='1')
	//{
		this->Entite::u();
		for(int i = 0; i < 1; i++)
			this->Entite::l();

		this->Entite::u();
		for(int i = 0; i < 1; i++)
			this->Entite::r();
	//}
}

bool Mechant::traj(){

	try{
		if (get_hitBox().x > LARGEUR_TERRAIN-LARGEUR_MECHANT-40){
			if (id[1]=='1' && get_hitBox().y % 100 <= 50){
				Entite::d();
				direction="down";
			}
			else if (id[1]=='1' && !get_hitBox().y % 100 <= 50){
				Entite::l();
				direction="left";
			}
			else if(id[1]=='2' && get_hitBox().y % 100 <= 50){
				Entite::l();
				direction="left";
			}
			else if(id[1]=='2' && !get_hitBox().y % 100 <= 50){
				Entite::u();
				direction="up";
			}
			else throw string ("if 1: condition inconnue");
		}

		else if (get_hitBox().x < 40){
			if (id[1]=='1' && get_hitBox().y % 100 <= 50){
				Entite::r();
				direction="right";
			}
			else if (id[1]=='1' && !get_hitBox().y % 100 <= 50){
				Entite::d();
				direction="down";
			}
			else if(id[1]=='2' && get_hitBox().y % 100 <= 50){
				Entite::u();
				direction="up";
			}
			else if(id[1]=='2' && !get_hitBox().y % 100 <= 50){
				Entite::r();
				direction="right";
			}
			else throw string ("if 2: condition inconnue");
		}

		else{
			if (!strcmp(direction.c_str(),"right")){
				 Entite::r();
			 }
			else if (!strcmp(direction.c_str(),"left")){
				 Entite::l();
			 }
			else throw string ("if 3: condition inconnue");
		}
	}
	catch(string const& chaine){
        cerr<<chaine<<endl;
		cerr<<"pos x= "<<get_hitBox().x<<"pos y= "<<get_hitBox().y<<endl;
    }
	return testLim();
}


void Mechant::afficher(SDL_Renderer* pRenderer){
	SDL_Surface* surface=SDL_LoadBMP("texture/mechant.bmp");
	SDL_Texture* texture=SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &this-> get_hitBox().w, &this-> get_hitBox().h );
    SDL_RenderCopy(pRenderer,texture, NULL, &this-> get_hitBox() );
	SDL_DestroyTexture(texture);
}
