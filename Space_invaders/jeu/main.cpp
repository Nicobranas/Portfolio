#include "data.hpp"
#include "interface.hpp"
//#include "entite.hpp"
#include "player.hpp"
#include "input.hpp"
#include "laser.hpp"
#include "lutin.hpp"
#include "guerrier.hpp"
#include "mechant.hpp"

using namespace std;

//Gestiond des déplacements des joueurs
void move(Input& in,Player* Player1,Player* Player2){

	//we are looking flags to know how to move player2
    if(in.Key(SDL_SCANCODE_W)) Player1->u();
    if(in.Key(SDL_SCANCODE_S)) Player1->d();
    if(in.Key(SDL_SCANCODE_D)) Player1->r();
    if(in.Key(SDL_SCANCODE_A)) Player1->l();

    if(Player2->get_id()[1]=='2'){
        if(in.Key(SDL_SCANCODE_UP)) Player2->u();
        if(in.Key(SDL_SCANCODE_DOWN)) Player2->d();
        if(in.Key(SDL_SCANCODE_RIGHT)) Player2->r();
        if(in.Key(SDL_SCANCODE_LEFT)) Player2->l();
    }
    else if (Player2->get_id()[1]=='3'){
        cout<<"Le comportement de l'IA reste a definir"<<endl;
    }
}

// malgré le non-ordonnancement d'un set, on ne peut pas erase un élément de celui-ci lors du parcours,
// pour pallier a ce problème, on arrete le parcours du set puis le recommencons quand un erase est
// necessaire
// laser_set_move permet de faire bouger tout les lasers tout en gérant l'allocation memoire
void laser_set_move(set<shared_ptr<Laser>>& laser_set, SDL_Renderer* pRenderer){
    for (auto f : laser_set){
         if(!f->traj()){
             laser_set.erase(f);
             laser_set_move(laser_set,pRenderer);
             break;
         }
         f->afficher(pRenderer);
    }
}

void laser_set_collision(set<shared_ptr<Laser>>& laser_set,set<shared_ptr<Mechant>>& mechant_set,Player*& Player1,Player*& Player2){
    SDL_Rect collisionRectangle;
    int break_flag=0; //on a besoin de sortir de plusieurs for, break est trop faible
    for (auto f : laser_set){
         if (SDL_IntersectRect( &f->get_hitBox(), &Player1->get_hitBox(), &collisionRectangle) == SDL_TRUE && f->get_id()[1]!='1'){
             Player1->get_pdv()-=f->get_degats();
             laser_set.erase(f);
             laser_set_collision(laser_set,mechant_set,Player1,Player2);
             break;
         }
         if (SDL_IntersectRect( &f->get_hitBox(), &Player2->get_hitBox(), &collisionRectangle) == SDL_TRUE && f->get_id()[1]!='2'){
             Player2->get_pdv()-=f->get_degats();
             laser_set.erase(f);
             laser_set_collision(laser_set,mechant_set,Player1,Player2);
             break;
         }
         for(auto m : mechant_set)
             if (SDL_IntersectRect( &f->get_hitBox(), &m->get_hitBox(), &collisionRectangle) == SDL_TRUE){
                 m->get_pdv()-=f->get_degats();
                 if (m->get_pdv()<=0) mechant_set.erase(m);
                 laser_set.erase(f);
                 break_flag=1;
                 laser_set_collision(laser_set,mechant_set,Player1,Player2);
                 break;
             }
        if (break_flag==1) break;
     }
}

void mechant_set_move(set<shared_ptr<Mechant>>& mechant_set, SDL_Renderer* pRenderer){
    for (auto f : mechant_set){
         if(!f->traj()){
             mechant_set.erase(f);
             mechant_set_move(mechant_set,pRenderer);
             break;
         }
         f->afficher(pRenderer);
    }
}

void mechant_set_collision(set<shared_ptr<Mechant>>& mechant_set,Player*& Player1, Player*& Player2){
    SDL_Rect collisionRectangle;
    for (auto f : mechant_set){
        /*if (f->get_pdv()<=0){
            mechant_set.erase(f);
            mechant_set_collision(mechant_set,Player1,Player2);
            break;
        }*/
        if (SDL_IntersectRect( &f->get_hitBox(), &Player1->get_hitBox(), &collisionRectangle) == SDL_TRUE){
            Player1->get_pdv()-=f->get_degats();
            mechant_set.erase(f);
            mechant_set_collision(mechant_set,Player1,Player2);
            break;
        }
        if (SDL_IntersectRect( &f->get_hitBox(), &Player2->get_hitBox(), &collisionRectangle) == SDL_TRUE){
            Player2->get_pdv()-=f->get_degats();
            mechant_set.erase(f);
            mechant_set_collision(mechant_set,Player1,Player2);
            break;
        }
    }
}

//Initialisation des joueurs, besoin de passer par des références de pointeurs pour initialiser les Players
void init_Player(Player*& Player1,Player*& Player2,int argc,char* argv[]){

    try{
        switch (argc){
            case 1:
                Player1=new Guerrier("p1");
                Player2=new Lutin("p2");
                break;
            case 2: //Cas d'une IA: on cree un guerrier comme IA
                if (!strcmp(argv[1],"Guerrier"))
                    Player1=new Guerrier("p1");
                else if (!strcmp(argv[1],"Lutin"))
                    Player1=new Lutin("p1");
                else
                    throw string ("Classe de personnage non-reconnue");
                Player2=new Guerrier("p3");
            case 3:
                if (!strcmp(argv[1],"Guerrier"))
                    Player1=new Guerrier("p1");
                else if (!strcmp(argv[1],"Lutin"))
                    Player1=new Lutin("p1");
                else
                    throw string ("Classe de personnage non-reconnue");

                if (!strcmp(argv[2],"Guerrier"))
                    Player2=new Guerrier("p2");
                else if (!strcmp(argv[2],"Lutin"))
                    Player2=new Lutin("p2");
                else
                    throw string ("Classe de personnage non-reconnue");
                break;
            default:
                throw string ("Nombre d'arguments invalide");
                break;
        }
    }
    catch(string const& chaine){
        cerr<<chaine<<endl;
    }
}

int main(int argc, char* argv[]){

    //Initialisation de l'interface
    Interface* interface = new Interface();

    //Initialisation des joueurs
    Player* Player1;
    Player* Player2;
    init_Player(Player1,Player2,argc,argv);

    //initialisation du gestionnaire de commandes
    Input in;                                           //Input = event control class

    //gestion laser
    set<shared_ptr<Laser>> laser_set;                   //Set for laser controls
    Uint32 P1_timer = SDL_GetTicks();                   //a timer to know when was the last shot of a player
    Uint32 P2_timer = SDL_GetTicks();
    unsigned int numlaser=0;                            //number of lasers

    //gestion mechants
    set<shared_ptr<Mechant>> mechant_set;
    Uint32 spawn_timer = SDL_GetTicks();
    unsigned int num_mechant=0;


    //SPAWN INITIAL DE 5 ENNEMIS PAR JOUEUR
    for(int i = 0; i < 5; i++)
    {
        string str = to_string(num_mechant++);
        while(str.size()<10) str="0"+str;
        shared_ptr<Mechant> a (new Mechant ("m2"+str));
        mechant_set.insert(a);
    }
    for(int i = 0; i < 5; i++)
    {
        string str = to_string(num_mechant++);
        while(str.size()<10) str="0"+str;
        shared_ptr<Mechant> a (new Mechant ("m1"+str));
        mechant_set.insert(a);
    }

    //flag disans qui a gagne
    int winner=0;

    while (!in.Quit()){

        interface->MAJ_Partie1(Player1,Player2);

        //GESTION DE LA MISE EN PAUSE
        while(in.Key(SDL_SCANCODE_ESCAPE)) in.Key(SDL_SCANCODE_ESCAPE)=in.escape();

        //GESTION DES FPS, 1ere PARTIE
      	unsigned int time_sync;
        unsigned int lasttime = SDL_GetTicks();

        //AFFICHAGE DES PLAYERS
        Player1->afficher(interface->get_Renderer());
        Player2->afficher(interface->get_Renderer());

        //GESTION DES EVENEMENTS
        in.Update();
        move(in,Player1,Player2);

        //GESTION DES TIRS
        if (SDL_GetTicks()-P1_timer>Player1->get_cadence()){

            string str = to_string(numlaser++);
            while(str.size()<6) str="0"+str;
            shared_ptr<Laser> a (new Laser ("l1"+str,Player1->get_hitBox().x-LARGEUR_LASER/2+Player1->get_hitBox().w/2,Player1->get_hitBox().y,Player1->get_degats()));
            laser_set.insert(a);
            P1_timer=SDL_GetTicks();

        }

        if (SDL_GetTicks()-P2_timer>Player2->get_cadence()){
            string str = to_string(numlaser++);
            while(str.size()<6) str="0"+str;
            shared_ptr<Laser> a (new Laser ("l2"+str,Player2->get_hitBox().x-LARGEUR_LASER/2+Player2->get_hitBox().w/2,Player2->get_hitBox().y,Player2->get_degats()));
            laser_set.insert(a);
            P2_timer=SDL_GetTicks();
        }

        /*if (SDL_GetTicks()-spawn_timer>1000){
            string str = to_string(num_mechant++);
            while(str.size()<10) str="0"+str;
            shared_ptr<Mechant> m1 (new Mechant ("m1"+str));
            mechant_set.insert(m1);
            str = to_string(num_mechant++);
            while(str.size()<10) str="0"+str;
            shared_ptr<Mechant> m2 (new Mechant ("m2"+str));
            mechant_set.insert(m2);
            spawn_timer=SDL_GetTicks();
        }*/

        //SPAWN DES ENNEMIS



        laser_set_collision(laser_set,mechant_set,Player1,Player2);
        laser_set_move(laser_set,interface->get_Renderer());
        mechant_set_collision(mechant_set,Player1,Player2);
        mechant_set_move(mechant_set,interface->get_Renderer());

        //gestion poursuite des mechants vers les joueurs
        //gobelin1.purchase();

        if (Player1->get_pdv()<=0){
            in.Quit()=1;
            winner=2;
        }
        else if (Player2->get_pdv()<=0){
            in.Quit()=1;
            winner=1;
        }

        //interface->MAJ_Partie1(Player1,Player2);
        SDL_RenderPresent(interface->get_Renderer());

        //GESTION DES FPS, 2eme PARTIE
        time_sync = SDL_GetTicks()-lasttime;  // ici, je calcule le temps écoulé depuis la dernière frame
    	if (time_sync<20)							// s'il ne s'est pas encore passé 20 millisecondes, j'attends.
    		SDL_Delay(20-time_sync);			   // ainsi, je synchronise mon application à 50 FPS (20*50 = 1000).

    }

    if (winner!=0){
        in.Quit()=0;
        while(in.Quit()==0){
            interface->FIN(winner);
            in.Update();
        }
    }

    delete Player1;
    delete Player2;
	delete interface;

	return EXIT_SUCCESS;
}
