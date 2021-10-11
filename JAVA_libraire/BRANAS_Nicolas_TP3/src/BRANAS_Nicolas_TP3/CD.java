package BRANAS_Nicolas_TP3;

public class CD extends Medium {

	private String duree;
	private int nbrSons;
	
	/**
	 * initialisation pas importante
	 * @param titre
	 * @param auteur
	 */
	public CD(String titre, String auteur) {
		super(titre,auteur);
		this.duree="00:00:00";
		this.nbrSons=0;
	}
	
	/**
	 * affichage rapide des donnees
	 */
	public void affiche() {
		System.out.println("affichage d'un CD");
		super.affiche();
		System.out.println(this.duree+" "+String.valueOf(this.nbrSons));
	}

	
}
