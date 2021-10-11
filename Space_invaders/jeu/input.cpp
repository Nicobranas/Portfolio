#include "input.hpp"

Input::Input()
{
	memset(this,0,sizeof(*this));
}

//fonction pour quitter le mode pause
int Input::escape()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
		switch (event.type){
			case (SDL_KEYDOWN):
				if(SDL_GetScancodeFromKey(event.key.keysym.sym) == SDL_SCANCODE_ESCAPE)
					return 0;
				break;
			case SDL_QUIT:
				quit = 1;
				return 0;
				break;
			default: break;
		}
	return 1;
}

void Input::Update()
{
	SDL_Event event;
    //mousebuttons[SDL_BUTTON_WHEELUP] = 0;
    //mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				key[SDL_GetScancodeFromKey(event.key.keysym.sym)]=1;
				break;
			case SDL_KEYUP:
				key[SDL_GetScancodeFromKey(event.key.keysym.sym)]=0;
				break;
			/*case SDL_MOUSEMOTION:
				mousex=event.motion.x;
				mousey=event.motion.y;
				mousexrel=event.motion.xrel;
				mouseyrel=event.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousebuttons[event.button.button]=1;
				break;
			case SDL_MOUSEBUTTONUP:
	            if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
	  				mousebuttons[event.button.button]=0;
				break;*/
			case SDL_QUIT:
				quit = 1;
				break;
			default:
				break;
		}
	}
}
