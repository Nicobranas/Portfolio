#include "player.hpp"

//Constructor:
Player::Player(const string id, int largeur, int hauteur){

	this->id=id;

	int pos[2];

	if (id[0]=='p' && id[1]=='1'){
	//if (id=="p1"){
		this->lim[0]=1;
		this->lim[1]=LARGEUR_TERRAIN-largeur-1;
		this->lim[2]=1;
		this->lim[3]=(HAUTEUR_TERRAIN-HAUTEUR_ZONE_MILIEU)/2-hauteur-1;
		pos[0]=LARGEUR_TERRAIN/2-largeur/2;
		pos[1]=(HAUTEUR_TERRAIN-HAUTEUR_ZONE_MILIEU)/4-hauteur/2;
	}

	else if (id[0]=='p' && (id[1]=='2' || id[1]=='3')){ //On traite de la meme maniere l'IA que le joueur deux
	//else if (id=="p2"){
		this->lim[0]=1;
		this->lim[1]=LARGEUR_TERRAIN-largeur-1;
		this->lim[2]=(HAUTEUR_TERRAIN-HAUTEUR_ZONE_MILIEU)/2+HAUTEUR_ZONE_MILIEU+1;
		this->lim[3]=HAUTEUR_TERRAIN-hauteur-1;
		pos[0]=LARGEUR_TERRAIN/2-largeur/2;
		pos[1]=(HAUTEUR_TERRAIN+(HAUTEUR_TERRAIN-HAUTEUR_ZONE_MILIEU)/2+HAUTEUR_ZONE_MILIEU)/2-hauteur/2;
	}

	else throw (runtime_error("player id have to be p1 or p2"));

	SDL_Rect box{pos[0], pos[1], largeur, hauteur};
	this->hitBox= box;

}

//Destructor:
Player::~Player(){
	//cout<<"delete"<<endl;
}

//Movement:
bool Player::testLim(){ //Verification if we are inside the limits
	if (hitBox.x>lim[1]) hitBox.x-=speed;
	if (hitBox.x<lim[0]) hitBox.x+=speed;
	if (hitBox.y<lim[2]) hitBox.y+=speed;
	if (hitBox.y>lim[3]) hitBox.y-=speed;

	return true;
}

void Player::r(){
	Entite::r();
	testLim();
}
void Player::l(){
	Entite::l();
	testLim();
}
void Player::u(){
	Entite::u();
	testLim();
}
void Player::d(){
	Entite::d();
	testLim();
}
