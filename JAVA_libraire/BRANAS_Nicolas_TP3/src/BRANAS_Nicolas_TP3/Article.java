package BRANAS_Nicolas_TP3;

public class Article extends Medium{
	
	private String nomMagazine;
	private int numero;
	private String intervalle;
	
	/**
	 * initialisation pas importante
	 * @param titre
	 * @param auteur
	 */
	public Article(String titre, String auteur) {
		super(titre,auteur);
		this.nomMagazine="inconnu";
		this.numero=0;
		this.intervalle="jspcequecarepresente";
	}
	
	/**
	 * affichage rapide des donnees
	 */
	public void affiche() {
		System.out.println("affichage d'un Article");
		super.affiche();
		System.out.println(this.nomMagazine+" "+String.valueOf(this.numero)+" "+this.intervalle);
	}
	
}
