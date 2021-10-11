#include "interface.hpp"

/*void MyAudioCallback(void* userdata, Uint8* stream, int streamlength)
{
    AudioData* audio = (AudioData*)userdata;

    if(audio -> length == 0) return ;

    Uint32 length = (Uint32)streamlength;
    length = (length > audio -> length ? audio -> length : length);
    SDL_memcpy(stream, audio-> pos, length);

    audio -> pos += length;
    audio -> length;
}*/

/*int Interface_Audio_Init(){

    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;

    if(SDL_LoadWAV("soundsEffects/TownTheme.wav", &wavSpec, &wavStart, &wavLength) == NULL)
    {
        std::cerr << "Erreur : soundsEffects/TownTheme.wav : impossimble de charger le fichier audio "<< std::endl;
        return 1;
    }

    AudioData audio;
    audio.pos = wavStart;
    audio.length = wavLength;
    wavSpec.callback = MyAudioCallback;
    wavSpec.userdata = &audio;

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if(device == 0)
    {
        std ::cerr <<"Erreur : " << SDL_GetError() << std::endl;
        return -1;
    }

    return 0;

}*/

Interface::Interface(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
    }

    pWindow=SDL_CreateWindow("SDL Programme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_TERRAIN+LARGEUR_MENU, HAUTEUR_TERRAIN, SDL_WINDOW_SHOWN);
    if(pWindow == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
    }
    pRenderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(pRenderer == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
    }
    SDL_Surface* im_terrain=SDL_LoadBMP("texture/terrain_Nuit.bmp");
    t_terrain=SDL_CreateTextureFromSurface(pRenderer, im_terrain);
    SDL_FreeSurface(im_terrain);

    if(SDL_QueryTexture(t_terrain, NULL, NULL, &rect_terrain.w, &rect_terrain.h) !=0){
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
    }

    if (TTF_Init() < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }

    police=TTF_OpenFont("police/esparac.ttf", 18);
    if (police == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }

}

Interface::~Interface(){
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_DestroyTexture(t_terrain);
    SDL_FreeSurface(text);
    TTF_CloseFont(police);
    SDL_DestroyTexture(t_text);
    SDL_Quit();
    TTF_Quit();
}

void Interface::MAJ_Partie1(Player* Player1, Player* Player2){

    //COLORIER LE FOND DE LA FENETRE
    SDL_SetRenderDrawColor(pRenderer, 50, 50, 50, 255); // on chosit une couleur
    SDL_RenderClear(pRenderer);                         // On applique la couleur a la fenetre

    SDL_RenderCopy(pRenderer, t_terrain, NULL, &rect_terrain);

    string pv = "Pv J1 = " + to_string(Player1->get_pdv()) + "; Pv J2= " + to_string(Player2->get_pdv());
    text=TTF_RenderText_Solid(police, pv.c_str(), SDL_Color{ 255, 255, 255, 255 });
    if (text == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }
    SDL_Texture* t_text=SDL_CreateTextureFromSurface(pRenderer, text);
    if (t_text == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }
    SDL_QueryTexture(t_text, nullptr, nullptr, &position.w, &position.h); // Récupere la dimension de la texture
    position.x=1000;
    position.y=200;
    SDL_RenderCopy(pRenderer, t_text, NULL, &position);

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(pRenderer, &zone_milieu);

}

void Interface::MAJ_Partie2(){
    //MISE A JOUR AFFICHAGE
    SDL_RenderPresent(pRenderer);
}

void Interface::FIN(int winner){

    SDL_Surface* im_terrain;
    if (winner==1) im_terrain=SDL_LoadBMP("texture/Player1.bmp");
    else if (winner==2) im_terrain=SDL_LoadBMP("texture/Player2.bmp");
    t_terrain=SDL_CreateTextureFromSurface(pRenderer, im_terrain);
    SDL_FreeSurface(im_terrain);

    SDL_SetRenderDrawColor(pRenderer, 50, 50, 50, 255); // on chosit une couleur
    SDL_RenderClear(pRenderer);                         // On applique la couleur a la fenetre

    SDL_RenderCopy(pRenderer, t_terrain, NULL, &rect_terrain);

    if(SDL_QueryTexture(t_terrain, NULL, NULL, &rect_terrain.w, &rect_terrain.h) !=0){
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
    }

    SDL_RenderPresent(pRenderer);
}
