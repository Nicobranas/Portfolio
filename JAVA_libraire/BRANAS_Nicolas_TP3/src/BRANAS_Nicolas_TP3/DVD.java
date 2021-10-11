package BRANAS_Nicolas_TP3;

public class DVD extends Medium {
	
	private String duree;
	
	/**
	 * constructeur initialisant la duree a "00:00:00" car pas important
	 * @param titre
	 * @param auteur
	 */
	public DVD(String titre, String auteur) {
		super(titre,auteur);
		this.duree="00:00:00";
	}
	
	/**
	 * affichage rapide des donnees
	 */
	public void affiche() {
		System.out.println("affichage d'un DVD");
		super.affiche();
		System.out.println(this.duree);
	}

}
