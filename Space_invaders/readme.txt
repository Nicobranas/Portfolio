Read me 
Projet C++ ROB 4
Haftman-Bouteloup Alexandre
Branas-Ybres Nicolas

Bibliothèques utilisés : 
	SDL2
	SDL_TTF2

commande pour compiler : make
commande pour exécuter : 
	Dans le cas où l’on souhaite choisir sa classe: ./exec classe1 classe2
	Dans le cas où l’on ne souhaite pas choisir sa classe: ./exec
	Dans le cas où l’on veut jouer contre une IA (pas implémenter): ./exec classe1

Les deux classes possibles sont “Guerrier” et “Lutin”
Le Guerrier ayant plus de vie et faisant plus de dégâts, le lutin se distingue par sa vitesse.


Présentation du jeu : 
Le jeu est inspiré de “space invaders”, mais en 1 Versus 1, il est symétrique par rapport à l'horizontale.

Règles du jeu : 
Les deux joueurs tirent des missiles de manière automatique à une certaine cadence (variant selon la classe choisis).
Des méchants apparaissent au milieu du terrain de manière aléatoire et se dirigent vers l’un des joueurs.
Les méchants peuvent êtres détruits par les lasers des deux joueurs ou lorsqu’ils touchent un joueur.
Un joueur perd des points de vie quand il se fait toucher par un laser adverse ou par un méchant.
Un joueur perd la partie lorsqu’il n’a plus de points de vie.
Le but du jeu est donc de survivre plus longtemps que son adversaire.


touches : 
déplacement joueur du haut (J1):             déplacement joueur du bas (J2): 
	z = haut                        			croix directionnelles    
	q = gauche
	s = bas
	d = droite

Pour mettre le jeu en pause : échap


