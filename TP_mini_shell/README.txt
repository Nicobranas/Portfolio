Sommaire:
I/Objectif de l'exercice
II/Comment utiliser le shell
III/Presentation sommaire du programme
IV/Nos problèmes

I/Objectif de l'exercice
Le but de cet exercice fût de faire un shell.
Nous avons permis d'éxecuter un programme avec un ou plusieurs arguments, dont
builtins cd et pwd
Puis nous avons intégré les fonctionnalités d'arrière-plan, de tuyau, et de
redirection.
Enfin nous avons rajouté la possibilité d'exécuter des chaines de commandes.

II/Comment utiliser le shell
Ouvrez un terminal dans le dossier du programme.
Compilez avec make (vous pouve clean avec make clean).
Exécutez avec ./exec.
Tapez votre commande.
Pour enregistrer le résultat du shell dans un fichier: "commande > fichier"
Pour exécuter en arrière-plan: "commande &"   (avec ou sans espace)
Pour exécuter plusieurs programmes: "commande; commande;..."

III/Presentation sommaire du programme
Voir schéma.

IV/Nos problèmes
Après l'utilisation d'un pipe, vous sortez du shell.
Pour exécuter plusieurs programmes, dont un avec un pipe, mettez la commande
comprenant le pipe comme dernière fonction.
Toutes les variables allouées ne sont pas libérées.
