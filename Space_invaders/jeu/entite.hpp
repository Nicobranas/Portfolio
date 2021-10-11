#ifndef ENTITE_HPP
#define ENTITE_HPP

#include "data.hpp"

class Entite{

protected:

	string id;
	int lim[4];	//[l r u d]
	int speed;
	SDL_Rect hitBox;
	int pdv;
	int degats;

public:

	//Operator:
	bool operator<(const Entite& o) const{return this->id<o.id;}

	//Getters and Setters:
	const SDL_Rect& get_hitBox() const{return this->hitBox;}
	SDL_Rect& get_hitBox() {return this->hitBox;}
	const string& get_id() const{return this->id;}
	string& get_id() {return this->id;}
	const int& get_pdv() const{return this->pdv;}
	int& get_pdv() {return this->pdv;}
	const int& get_degats() const{return this->degats;}
	int& get_degats() {return this->degats;}


	//Collision
	void collision(const Entite& e, SDL_Rect& collisionRectangle);
	//void testContact(Entite e);

	//Affichage
	virtual void afficher(SDL_Renderer* pRenderer)=0;

	//Movements:

	bool testLim();
	void r();					//u=up,d=down,l=left,r=right
	void l();
	void u();
	void d();

};

#endif
