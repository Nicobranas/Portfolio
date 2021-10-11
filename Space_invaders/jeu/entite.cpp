#include "entite.hpp"

/*
void Entite::testContact(Entite e)
{

}
*/
//Movements:

void Entite::r(){this->hitBox.x+=speed;}
void Entite::l(){this->hitBox.x-=speed;}
void Entite::u(){
	this->hitBox.y-=speed;
	//cout<<"position y= "<<get_hitBox().y<<endl;
}
void Entite::d(){this->hitBox.y+=speed;}

bool Entite::testLim(){
	if (hitBox.x>=lim[1]) return false;
	if (hitBox.x<=lim[0]) return false;
	if (hitBox.y<=lim[2]) return false;
	if (hitBox.y>=lim[3]) return false;
	return true;
}

void Entite::collision(const Entite& e, SDL_Rect& collisionRectangle)
{
	if (SDL_IntersectRect( &this->get_hitBox(), &e.get_hitBox(), &collisionRectangle) == SDL_TRUE )
    //if (SDL_IntersectRect( &(Player1->get_hitBox()) , &(Player2->get_hitBox()), NULL) == SDL_TRUE )
    {
        //SDL_Log("[DEBUG] Il y 'a collision ici ..."); // j'affiche ce message lorsqu'il y a collision
        //cout << "colision entre : " << this->id << "et  : "  << e.id << endl;

				if(this->get_id()[1] != e.get_id()[1] || this->get_id()[0]=='m')
				{
					//cout <<" joueur  : " << this->get_id() << "touché ! " << endl;
					this->get_pdv()-=1;
				}
    }
}
