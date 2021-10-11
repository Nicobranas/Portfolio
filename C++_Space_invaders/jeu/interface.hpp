#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "data.hpp"
#include "player.hpp"

struct AudioData
{
    Uint8* pos;
    Uint32 length;
};

void InterfaceClose(SDL_Window* pWindow,SDL_Renderer* pRenderer);

class Interface{

    protected:
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;
        SDL_Texture* t_terrain;
        SDL_Rect zone_milieu{0, (HAUTEUR_TERRAIN - HAUTEUR_ZONE_MILIEU)/2, LARGEUR_TERRAIN, HAUTEUR_ZONE_MILIEU};
        SDL_Rect rect_terrain{0,0,LARGEUR_TERRAIN, HAUTEUR_TERRAIN};
        //SDL_Surface* im_terrain;

        TTF_Font* police;
        SDL_Surface* text;
        SDL_Texture* t_text;
        SDL_Rect position;

    public:
        Interface();
        ~Interface();
        void MAJ_Partie1(Player* Player1, Player* Player2);
        void MAJ_Partie2();
        void FIN(int winner);

        const SDL_Renderer* get_Renderer() const{return this->pRenderer;}
    	SDL_Renderer* get_Renderer() {return this->pRenderer;}

        const SDL_Rect& get_zone_milieu() const{return this->zone_milieu;}
    	SDL_Rect& get_zone_milieu() {return this->zone_milieu;}

};


#endif
