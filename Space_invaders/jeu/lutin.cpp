#include "lutin.hpp"

Lutin::Lutin(const string id) : Player(id, LARGEUR_LUTIN, HAUTEUR_LUTIN){

	this->speed=4;
	this->cadence=1000;
	this->pdv=80;
	this->degats=10;

}

void Lutin::afficher(SDL_Renderer* pRenderer){
	SDL_Surface* surface=SDL_LoadBMP("texture/wizard.bmp");
	SDL_Texture* texture=SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &this-> get_hitBox().w, &this-> get_hitBox().h );
    SDL_RenderCopy(pRenderer,texture, NULL, &this-> get_hitBox() );
	SDL_DestroyTexture(texture);
}
