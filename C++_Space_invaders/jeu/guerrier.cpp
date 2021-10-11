#include "guerrier.hpp"

Guerrier::Guerrier(const string id) : Player(id, LARGEUR_GUERRIER, HAUTEUR_GUERRIER){

	this->speed=2;
	this->cadence=1000;
	this->pdv=100;
	this->degats=15;

}

void Guerrier::afficher(SDL_Renderer* pRenderer){
	SDL_Surface* surface=SDL_LoadBMP("texture/knight2.bmp");
	SDL_Texture* texture=SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &this-> get_hitBox().w, &this-> get_hitBox().h );
    SDL_RenderCopy(pRenderer,texture, NULL, &this-> get_hitBox() );
	SDL_DestroyTexture(texture);
}
