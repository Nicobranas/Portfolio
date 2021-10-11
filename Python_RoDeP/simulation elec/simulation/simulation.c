#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

//Mroue=Pololu 131:1 (ref:4756)
//Mser=24BYJ48 (pas à pas)
//Mlev=24BYJ48 (pas à pas)




int main(int argc, char** argv){

	perif Mroue={5.5,0.740,0};
	perif Mser={0.300,0.150,0};
	perif Mlev={0.300,0.150,0};


	//il est difficile d'estimer la consommation des différents composants, les estimations sont donc grossières.

	perif Ard={2,0.700,0.03};				//arduino
	perif Rasp={2,0.700,0.03};			//rasperry 3B
	perif Cam={0.140,0.140,0};			//camera
	perif Led={0.1,0.1,0}; 				//pour 5 leds


	float t=0;						//compteur
	float ttrajet=3;						//temps du premier trajet (3m de dist a 1m/s)
	const int tscan=120;				//temps de scan
	const int tprise=2;
	int cycle=1;						//nombre de cycle
	float conso=0;						//intensite consomme au total


	while (cycle<=100){

		float c=0;						//intensite consomme pendant le cycle
		float A;
		printf("%f\n",t);
		printf("%f\n",c);
		printf("%f\n",A);
		//scanner a stockage
		t+=ttrajet;
		A=ttrajet*(2*Mroue.normal+Mser.min+Mlev.min+Ard.normal+Rasp.normal+Cam.normal+Led.normal);		//valeur intermediaire à reconvertir
		c+=A/3600;

		printf("%f\n",t);
		printf("%f\n",c);
		printf("%f\n",A);

		//prise
		t+=tprise;
		A=tprise*(2*Mroue.min+Mser.max+Mlev.max+Ard.normal+Rasp.normal+Cam.normal+Led.normal);			//valeur intermediaire à reconvertir
		//A=tprise*(2*Mroue.min+Mser.normal+Mlev.normal+Ard.normal+Rasp.min+Cam.min+Led.min);
		c+=A/3600;

		//stockage a scanner
		t+=ttrajet;
		A=ttrajet*(2*Mroue.normal+Mser.normal+Mlev.normal+Ard.normal+Rasp.normal+Cam.normal+Led.normal);		//valeur intermediaire à reconvertir
		c+=A/3600;

		//scan
		t+=tscan;
		A=tscan*(2*Mroue.min+Mser.normal+Mlev.normal+Ard.min+Rasp.min+Cam.min+Led.min);							//valeur intermediaire à reconvertir
		c+=A/3600;

		//scanner a destockage
		t+=ttrajet;
		A=ttrajet*(2*Mroue.normal+Mser.normal+Mlev.normal+Ard.normal+Rasp.normal+Cam.normal+Led.normal);		//valeur intermediaire à reconvertir
		c+=A/3600;

		//depot
		t+=tprise;
		A=tprise*(2*Mroue.min+Mser.max+Mlev.max+Ard.normal+Rasp.normal+Cam.normal+Led.normal);			//valeur intermediaire à reconvertir
		//A=tprise*(2*Mroue.min+Mser.normal+Mlev.normal+Ard.normal+Rasp.min+Cam.min+Led.min);
		c+=A/3600;

		//destockage a scanner
		t+=ttrajet;
		A=ttrajet*(2*Mroue.normal+Mser.min+Mlev.min+Ard.normal+Rasp.normal+Cam.normal+Led.normal);		//valeur intermediaire à reconvertir
		c+=A/3600;

		ttrajet+=0.5; //on estime que le prochain pot sera plus loin de 50cm
		conso+=c;
		printf("au cycle %d j'ai consomme %f Ah\n",cycle,c);
		cycle++;
	}

	printf("conso total=%f Ah\n",conso);
	printf("temps total=%f h\n",t/3600);

	return 0;
}
