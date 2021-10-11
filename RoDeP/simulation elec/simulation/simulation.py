#Liste des choses à faire: transmission des données entre raspberry et arduino



#ici on initialise les périphériques, 0=consomax, 1=consonormal, 2=consominimal

Mroue = [5.5,0.740,0]
Mser = [0.300,0.150,0]
Mlev = [0.300,0.150,0]

Ard = [2,0.700,0.03]
Rasp = [2,0.700,0.03]
Cam = [0.140,0.140,0]
Led = [0.1,0.1,0]

#ici on initialise le reste

t=0;						#compteur
ttrajet=3;					#temps du premier trajet (3m de dist a 1m/s)
tscan=120;					#temps de scan
tprise=2;
cycle=1;					#numéro de cycle
nbr_cycle=100;
conso=0;	

while cycle < nbr_cycle+1:

		c=0;						#intensite consomme pendant le cycle
		A=0;

		#scanner a stockage
		t=t+ttrajet;
		A=ttrajet*(2*Mroue[1]+Mser[2]+Mlev[2]+Ard[1]+Rasp[1]+Cam[1]+Led[1]);		#valeur intermediaire à reconvertir
		c=c+A/3600;

		#prise
		t=t+tprise;
		A=tprise*(2*Mroue[2]+Mser[0]+Mlev[0]+Ard[1]+Rasp[1]+Cam[1]+Led[1]);			#valeur intermediaire à reconvertir
		#A=tprise*(2*Mroue[2]+Mser[1]+Mlev[1]+Ard[1]+Rasp[2]+Cam[2]+Led[2]);
		c=c+A/3600;

		#stockage a scanner
		t=t+ttrajet;
		A=ttrajet*(2*Mroue[1]+Mser[1]+Mlev[1]+Ard[1]+Rasp[1]+Cam[1]+Led[1]);		#valeur intermediaire à reconvertir
		c=c+A/3600;

		#scan
		t=t+tscan;
		A=tscan*(2*Mroue[2]+Mser[1]+Mlev[1]+Ard[2]+Rasp[2]+Cam[2]+Led[2]);							#valeur intermediaire à reconvertir
		c=c+A/3600;

		#scanner a destockage
		t=t+ttrajet;
		A=ttrajet*(2*Mroue[1]+Mser[1]+Mlev[1]+Ard[1]+Rasp[1]+Cam[1]+Led[1]);		#valeur intermediaire à reconvertir
		c=c+A/3600;

		#depot
		t=t+tprise;
		A=tprise*(2*Mroue[2]+Mser[0]+Mlev[0]+Ard[1]+Rasp[1]+Cam[1]+Led[1]);			#valeur intermediaire à reconvertir
		#A=tprise*(2*Mroue[2]+Mser[1]+Mlev[1]+Ard[1]+Rasp[2]+Cam[2]+Led[2]);
		c=c+A/3600;

		#destockage a scanner
		t=t+ttrajet;
		A=ttrajet*(2*Mroue[1]+Mser[2]+Mlev[2]+Ard[1]+Rasp[1]+Cam[1]+Led[1]);		#valeur intermediaire à reconvertir
		c=c+A/3600;

		ttrajet=ttrajet+0.5; #on estime que le prochain pot sera plus loin de 50cm
		conso=conso+c;
		print("au cycle ",cycle," j'ai consomme ",c," Ah")
		cycle=cycle+1;

print("conso total",conso," Ah");
print("temps total",t/3600," h")