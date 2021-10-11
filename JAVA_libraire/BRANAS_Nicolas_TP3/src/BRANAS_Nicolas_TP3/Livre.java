package BRANAS_Nicolas_TP3;

public class Livre extends Medium {

	private String editeur;
	private int nbrPages;
	
	/**
	 * initialisation pas importante
	 * @param titre
	 * @param auteur
	 */
	public Livre(String titre, String auteur) {
		super(titre,auteur);
		this.editeur="inconnu";
		this.nbrPages=0;
	}
	
	/**
	 * affichage rapide des donnees
	 */
	public void affiche() {
		System.out.println("affichage d'un Livre");
		super.affiche();
		System.out.println(this.editeur+" "+String.valueOf(this.nbrPages));
	}
	
}
