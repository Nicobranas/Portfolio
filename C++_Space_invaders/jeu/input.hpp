#ifndef INPUT_HPP
#define INPUT_HPP

#include "data.hpp"

class Input
{
protected:
	char key[512];
	int quit;

public:
	Input();
	~Input(){}
	void Update();
	int escape();
	char& Key(int i){return key[i];}
	const int& Quit() const{return this->quit;}
	int& Quit() {return this->quit;}

};


#endif
